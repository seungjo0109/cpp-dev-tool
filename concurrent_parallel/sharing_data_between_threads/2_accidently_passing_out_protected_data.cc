#include <iostream>
#include <mutex>
#include <string>

class SomeData
{
public:
    void DoSomething() { std::cout << "Do something\n"; }
private:
    int a;
    std::string b;
};

class DataWrapper
{
public:
    template<typename Function>
    void ProcessData(Function func){
        std::lock_guard<std::mutex> lg(m_);
        func(data);     // Pass "protected" data to user-supplied function
    }
private:
    std::mutex m_;
    SomeData data_;
};

SomeData* unprotected;

void MaliciousFunction(SomeData& protected_data)
{
    unprotected = &protected_data;
}

DataWrapper wrapper;
void Foo()
{
    wrapper.ProcessData(MaliciousFunction);     // Pass in a malicious function
    unprotected->DoSomething();                 // Unprotected access to protected data
}