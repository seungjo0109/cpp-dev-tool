#include <iostream>
#include <thread>

#include "scheduled_task_callback.hpp"

int count{0};

void MockFunction()
{
    count++;
    std::cout << "This is mocking function: " << count << " times\n";
}

int main()
{
    ScheduledTaskCallback task_callback;
    void* mock_coockie;

    // Register callback function
    task_callback.Add(MockFunction, 1000, &mock_coockie);

    while(true){
        task_callback.RunOnce();

        // Change scheduling time 500ms
        if(count == 10){
            task_callback.Change(500, mock_coockie);
        }
        // Remove task from entries
        if(count == 20){
            task_callback.Remove(mock_coockie);
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}