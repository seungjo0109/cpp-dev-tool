#include "blocking_queue.h"

#include <iostream>
#include <thread>

BlockingQueue<int> queue;

void Push()
{
    int i = 0;

    while(i<1000000){
        queue.Push(i);
        i++;
    }
}

void Pop()
{
    int i = 0;

    while(i<1000000){
        queue.Pop();
        i++;
    }
}

int main()
{
    std::thread t1(Push);
    std::thread t2(Pop);
    std::thread t3(Push);

    t1.join();
    t2.join();
    t3.join();

    std::cout << "queue size: " << queue.Size() << std::endl;
    std::cout << "clear queue" << std::endl;
    queue.Clear();
    std::cout << "queue size: " << queue.Size() << std::endl;

    return 0;
}