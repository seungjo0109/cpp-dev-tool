#include "blocking_intrusive_list.h"

#include <iostream>
#include <memory>
#include <thread>

class TestNode: public Node<TestNode* >
{
public:
    TestNode(int num): num_(num) {}

    void PrintNum(){std::cout << num_ << std::endl;}
    bool operator<=(const TestNode &rhs) const { return num_ <= rhs.num_;}
private:
    int num_;
};
BlockingIntrusiveList<TestNode *> list;

void Add()
{
    int i = 0;

    while(i<100){
        list.Add(new TestNode(i));
        i++;
    }
}

int main()
{
    std::thread t1(Add);
    std::thread t2(Add);
    std::thread t3(Add);
    t1.join();
    t2.join();
    t3.join();

    std::cout << "list size: " << list.Size() << std::endl;
    list.Clear();
    std::cout << "list size: " << list.Size() << std::endl;

    return 0;
}