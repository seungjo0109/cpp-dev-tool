#include <iostream>

class NonCopyable   // this class also not movable
{
public:
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};

class MyType : NonCopyable {};

/*
    A better approach would be to just add the two missing members
    (the move constructor and move assignment operator) explicitly.
*/
class MyTypeV2 
{
public:
    MyTypeV2() = default;
    MyTypeV2(const MyTypeV2&) = delete;
    MyTypeV2& operator=(const MyTypeV2 &) = delete;
    MyTypeV2(MyTypeV2&&) = delete;
    MyTypeV2& operator=(MyTypeV2 &&) = delete; 
};

int main()
{
    MyType obj1;
    // MyType obj2 = obj1;             //compile error: non-copyable
    // MyType obj2 = std::move(obj1);  //compile error: non-movable

    MyTypeV2 obj3;
    // MyTypeV2 obj4 = obj3;             //compile error: non-copyable
    // MyTypeV2 obj4 = std::move(obj3);  //compile error: non-movable

    return 0;
}

