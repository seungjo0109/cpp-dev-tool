#pragma once

#include <chrono>
#include <functional>
#include <memory>
#include <mutex>
#include <unordered_map>

// Refernce: https://github.com/mavlink/MAVSDK (CallEveryHandler)
class ScheduledTaskCallback
{
    using steady_time = std::chrono::time_point<std::chrono::steady_clock>;

    // Scheduled task entry
    struct TaskEntry{
        std::function<void()> callback{nullptr};
        steady_time last_time{};
        float interval_time{0.0};   // ms
    };

public:
    ScheduledTaskCallback() = default;
    ~ScheduledTaskCallback() = default;

    // Non copyable & movable
    ScheduledTaskCallback(ScheduledTaskCallback const&) = delete;
    ScheduledTaskCallback& operator=(ScheduledTaskCallback const&) = delete;

    void Add(std::function<void()> callback, float interval_time, void** cookie);
    void Change(float interval_time, const void* cookie);
    void Reset(const void* cookie);
    void Remove(const void* cookie);

    void RunOnce();

private:

    std::unordered_map<void*, std::shared_ptr<TaskEntry>> entries_{};
    std::mutex mutex_;
    bool iterator_invalidated_{false};
};

