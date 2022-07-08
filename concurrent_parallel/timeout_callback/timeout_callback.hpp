#pragma once

#include <chrono>
#include <functional>
#include <memory>
#include <mutex>
#include <unordered_map>

// Refernce: https://github.com/mavlink/MAVSDK (CallEveryHandler)
class TimeoutCallback
{
    using steady_time = std::chrono::time_point<std::chrono::steady_clock>;

    struct TimeoutTask
    {
        std::function<void()> callback{};
        steady_time time{};
        double duration{0.0};   // ms
    };

public:
    TimeoutCallback() = default;
    ~TimeoutCallback() = default;

    TimeoutCallback(TimeoutCallback const&) = delete;
    TimeoutCallback& operator=(TimeoutCallback const&) = delete;
    TimeoutCallback(TimeoutCallback&&) = delete;
    TimeoutCallback& operator=(TimeoutCallback&&) = delete;

    void Add(std::function<void()> callback, double duration, void** cookie);
    void Refresh(const void* cookie);
    void Remove(const void* cookie);
    void RunOnce();

private:

    std::unordered_map<void*, std::shared_ptr<TimeoutTask>> timeouts_{};
    std::mutex mutex_;
    bool iterator_invalidated_{false};
};