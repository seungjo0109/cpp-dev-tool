## Managing copyability and movability

* When designing a new type in C++, it's important to decide whether it should be copyable and movable. 
* There are cases when you don't want class to be copied. Classes that are very expensive to copy are one example. Another would be those subject to error due to slicing.
* In the past, a common way to prevent such objects from copying was by using the non-copyable idiom

</br>

``` c++
// non_copyable_movalbe.cc

class NonCopyable   // this class also not movable
{
public:
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};
```

</br>

* that such a class is also not movable, although it's easy to not notice it when reading the class definition.
* A better approach would be to just add the two missing members(the move constructor and move assignment operator) explicitly.
* __As a rule of thumb, when declaring such special member functions, always declare all of them__

</br>

``` c++
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

```

</br>

### reference: Software Architecture with C++: Design modern systems using effective architecture concepts, design patterns, and techniques with C++20