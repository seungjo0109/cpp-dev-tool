#include "blocking_stack.h"

#include <iostream>
#include <thread>

BlockingStack<int> stack;

void Push()
{
    int i = 0;

    while(i<1000000){
        stack.Push(i);
        i++;
    }
}

void Pop()
{
    int i = 0;

    while(i<1000000){
        stack.Pop();
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

    std::cout << "stack size: " << stack.Size() << std::endl;
    std::cout << "clear stack" << std::endl;
    stack.Clear();
    std::cout << "stack size: " << stack.Size() << std::endl;

    return 0;
}