#include <iostream>
#include <thread>

#include "timeout_callback.hpp"

void TaskCallback()
{
    std::cout << "Timeout callback function called\n";
}

int main()
{
    TimeoutCallback timeout_callback;
    void* cookie_5s_timeout; 
    void* cookie_6s_timeout;
    void* cookie_10s_timeout;

    timeout_callback.Add(TaskCallback, 5000, &cookie_5s_timeout);
    timeout_callback.Add(TaskCallback, 6000, &cookie_6s_timeout);
    timeout_callback.Add(TaskCallback, 10000, &cookie_10s_timeout);

    timeout_callback.Remove(cookie_6s_timeout);

    while(true)
    {
        static int count{0};
        count++;

        timeout_callback.RunOnce();     

        if(count == 400){  // 4sec
            timeout_callback.Refresh(cookie_5s_timeout);
            timeout_callback.Refresh(cookie_10s_timeout);
            std::cout << "Refresh timeout callback\n";
        }
        if(count == 2000){  // 20sec
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));   
    }

    return 0;
}