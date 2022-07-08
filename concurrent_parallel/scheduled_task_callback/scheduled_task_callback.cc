#include "scheduled_task_callback.hpp"

static uint64_t ElapsedMilliSec(std::chrono::time_point<std::chrono::steady_clock> time_prev)
{
    auto now = std::chrono::steady_clock::now().time_since_epoch();
    return static_cast<uint64_t>((now - time_prev.time_since_epoch()) / std::chrono::milliseconds(1));
}


void ScheduledTaskCallback::Add(std::function<void()> callback, float interval_time, void** cookie)
{
    auto entry = std::make_shared<TaskEntry>();
    entry->callback = std::move(callback);
    
    auto time_before = std::chrono::steady_clock::now();
    time_before -= std::chrono::milliseconds(int64_t(interval_time));

    entry->last_time = time_before;
    entry->interval_time = interval_time;

    void* new_cookie = static_cast<void*>(entry.get());

    {
        std::lock_guard<std::mutex> lg(mutex_);
        entries_.insert(std::pair<void*, std::shared_ptr<TaskEntry>>(new_cookie, entry));
    }

    if(cookie != nullptr){
        *cookie = new_cookie;
    }
}

void ScheduledTaskCallback::Change(float interval_time, const void* cookie)
{
    std::lock_guard<std::mutex> lg(mutex_);

    auto it = entries_.find(const_cast<void*>(cookie));
    if(it != entries_.end()){
        it->second->interval_time = interval_time;
    }
}

void ScheduledTaskCallback::Reset(const void* cookie)
{
    std::lock_guard<std::mutex> lg(mutex_);

    auto it = entries_.find(const_cast<void*>(cookie));
    if(it != entries_.end()){
        it->second->last_time = std::chrono::steady_clock::now();
    }
}

void ScheduledTaskCallback::Remove(const void* cookie)
{
    std::lock_guard<std::mutex> lg(mutex_);

    auto it = entries_.find(const_cast<void*>(cookie));
    if(it != entries_.end()){
        entries_.erase(const_cast<void*>(cookie));
        iterator_invalidated_ = true;
    }
}

void ScheduledTaskCallback::RunOnce()
{
    mutex_.lock();

    for(auto &entry: entries_){
        if (ElapsedMilliSec(entry.second->last_time) > double(entry.second->interval_time)) {
            entry.second->last_time += std::chrono::milliseconds(int64_t(entry.second->interval_time));

            if (entry.second->callback) {
                std::function<void()> callback = entry.second->callback;

                mutex_.unlock();
                callback();
                mutex_.lock();
            }
        }

        if (iterator_invalidated_) {
            iterator_invalidated_ = false;
            break;
        }
    }
}