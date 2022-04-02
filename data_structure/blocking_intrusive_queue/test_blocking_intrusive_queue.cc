#include "blocking_intrusive_queue.h"

#include <iostream>
#include <memory>
#include <thread>

class TestNode: public Node<TestNode* >
{
public:
    TestNode(int num): num_(num) {}
private:
    int num_;
};

BlockingIntrusiveQueue<TestNode *> queue;

void Push()
{
    int i = 0;

    while(i<10000){
        queue.Push(new TestNode(i));
        i++;
    }
}

int main()
{
    std::thread t1(Push);
    std::thread t2(Push);
    t1.join();
    t2.join();

    std::cout << "queue size: " << queue.Size() << std::endl;
    std::cout << "clear queue" << std::endl;
    queue.Clear();
    std::cout << "queue size: " << queue.Size() << std::endl;

    return 0;
}