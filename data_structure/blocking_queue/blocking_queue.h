#pragma once

#include <queue>
#include <mutex>

template<typename T>
class BlockingQueue
{
public:
    BlockingQueue(){}
    BlockingQueue(const BlockingQueue&) = delete;
    BlockingQueue& operator=(const BlockingQueue&) = delete;

    size_t Size(){ return queue_.size(); }

    void Push(T value)
    {
        std::lock_guard<std::mutex> lg(mutex_);
        queue_.push(std::move(value));
    }

    T Pop()
    {
        std::lock_guard<std::mutex>  lg(mutex_);
        
        auto value = queue_.front();
        queue_.pop();

        return value;
    }

    void Clear()
    {
        std::lock_guard<std::mutex> lg(mutex_);

        while(!queue_.empty()){
            queue_.pop();
        }
    }

private:

    std::queue<T> queue_;
    std::mutex mutex_;

};