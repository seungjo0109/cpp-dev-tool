#pragma once

#include <stack>
#include <mutex>

template<typename T>
class BlockingStack
{
public:
    BlockingStack(){}
    BlockingStack(const BlockingStack&) = delete;
    BlockingStack& operator=(const BlockingStack&) = delete;

    size_t Size() { return stack_.size(); }

    void Push(T value)
    {
        std::lock_guard<std::mutex> lg(mutex_);
        stack_.push(std::move(value));
    }

    T Pop()
    {
        std::lock_guard<std::mutex> lg(mutex_);
        auto value = stack_.top();
        stack_.pop();

        return value;
    }

    void Clear()
    {
        std::lock_guard<std::mutex> lg(mutex_);

        while(!stack_.empty()){
            stack_.pop();
        }
    }

private:

    std::stack<T> stack_;
    std::mutex mutex_;

};