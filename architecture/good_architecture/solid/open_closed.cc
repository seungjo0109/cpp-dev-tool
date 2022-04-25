#include <iostream>

/* 
    A great feature of C++ demonstrating this principle is `operator<<` of `ostream`.
    To extend it so that it supports your custom class, all you need to do is to write code similar to the following:
*/
template<typename T, typename U, typename V>
class Foo{

    template<typename X, typename Y, typename Z>
    friend std::ostream &operator<<(std::ostream &stream, const Foo<X,Y,Z> &foo);

public:
    Foo(T first, U second, V third): 
        first_(first), second_(second), secretThirdMember_(third){}

    T first_;
    U second_;
private:
    V secretThirdMember_;
};

template<typename T, typename U, typename V>
std::ostream &operator<<(std::ostream &stream, const Foo<T,U,V> &foo){
    stream << foo.first_ << '\n';
    stream << foo.second_ << '\n';
    stream << foo.secretThirdMember_ << '\n';
    return stream;
}

int main()
{
    auto foo = Foo<int, float, const char*>{10, 20.0, "foo"};
    std::cout << foo;
}