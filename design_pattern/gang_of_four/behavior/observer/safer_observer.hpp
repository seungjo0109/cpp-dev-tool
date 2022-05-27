#pragma once

#include <algorithm>
#include <mutex>
#include <string>
#include <vector>

// Observer class
template <typename T>
class SaferObserver
{
public:
    virtual void FieldChanged(
        T& source,
        const std::string& field_name
    ) = 0;
};

// thread-safe SaferObserver class
template<typename T>
class SaferObservalble
{
public:
    void Notify(T& source, const std::string& field_name)
    {
        std::scoped_lock<std::mutex> lock{mutex_};
        for(auto observer : observers_){
            if(observer){
                observer->FieldChanged(source, field_name);
            }
        }
    }

    void Subscribe(SaferObserver<T>& observer)
    {
        std::scoped_lock<std::mutex> lock{mutex_};
        observers_.push_back(&observer);
    }

    void Unsubscribe(SaferObserver<T>& observer)
    {
        auto iter = std::find(begin(observers_), end(observers_), &observer);
        if(iter != end(observers_)){
            *iter = nullptr;
        }
    }

private:
    std::vector<SaferObserver<T>*> observers_;
    std::mutex mutex_;
};