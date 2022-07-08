#include "timeout_callback.hpp"

void TimeoutCallback::Add(std::function<void()> callback, double duration, void** cookie)
{
    auto timeout_task = std::make_shared<TimeoutTask>();
    timeout_task->callback = callback;
    timeout_task->time = std::chrono::steady_clock::now() +
        std::chrono::milliseconds(int64_t(duration));
    timeout_task->duration = duration;

    void* new_cookie = static_cast<void*>(timeout_task.get());

    {
        std::lock_guard<std::mutex> lg(mutex_);
        timeouts_.insert(std::pair<void*, std::shared_ptr<TimeoutTask>>(new_cookie, timeout_task));
    }

    if(cookie != nullptr){
        *cookie = new_cookie;
    }
}

void TimeoutCallback::Refresh(const void* cookie)
{
    if(cookie == nullptr){
        return;
    }

    std::lock_guard<std::mutex> lg(mutex_);

    auto it = timeouts_.find(const_cast<void*>(cookie));
    if(it != timeouts_.end()){
        steady_time future_time = std::chrono::steady_clock::now() +
            std::chrono::milliseconds(int64_t(it->second->duration));
        it->second->time = future_time;
    }
}

void TimeoutCallback::Remove(const void* cookie)
{
    if(cookie == nullptr){
        return;
    }

    std::lock_guard<std::mutex> lg(mutex_);

    auto it = timeouts_.find(const_cast<void*>(cookie));
    if(it != timeouts_.end()){
        timeouts_.erase(const_cast<void*>(cookie));
        iterator_invalidated_ = true;
    }
}

void TimeoutCallback::RunOnce()
{
    mutex_.lock();

    steady_time now = std::chrono::steady_clock::now();

    for (auto it = timeouts_.begin(); it != timeouts_.end(); /* no ++it */) {
        // If time is passed, call timeout callback.
        if (it->second->time < now) {
            if (it->second->callback) {
                // Get a copy for the callback because we will remove it.
                std::function<void()> callback = it->second->callback;

                // Self-destruct before calling to avoid locking issues.
                timeouts_.erase(it++);

                // Unlock while we callback because it might in turn want to add timeouts.
                mutex_.unlock();
                callback();
                mutex_.lock();
            }

        } else {
            ++it;
        }

        // We start over if anyone has messed with this while we called the callback.
        if (iterator_invalidated_) {
            iterator_invalidated_ = false;
            it = timeouts_.begin();
        }
    }
    mutex_.unlock();
    
}