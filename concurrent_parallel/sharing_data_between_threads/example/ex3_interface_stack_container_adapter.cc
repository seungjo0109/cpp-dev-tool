#include <iostream>
#include <deque>
#include <stack>

template<typename T, typename Container=std::deque<T>>
class stack
{
public:
    explicit stack(cosnt Container&);
    explicit stack(Container&& = Container());
    template<class Alloc> explicit stack(const Alloc&);
    template<class Alloc> stack(const Container&, const Alloc&);
    template<class Alloc> stack(Container&&, const Alloc&);
    template<class Alloc> stack(stack&&, const Alloc&);

    bool empty() const;
    size_t size() const;
    T& top();
    T cosnt& top() const;
    void push(T const&);
    void push(T&&);
    void pop();
    void swap()(stack&&);
    template<class... Args> void emplace(Args&&... args);   // new in C++14
};