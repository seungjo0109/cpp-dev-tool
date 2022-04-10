## Single responsibility principle

* The Open-Closed Principle(OCP) means that code should be open for extension but closed for modification.
* Open for extension means that we could extend the list of types the code supports easily.
* Closed for modification means existing code shouldn't change, as this can often cause bugs somewhere else in the system.

</br>

* A great feature of C++ demonstrating this principle is `operator<<` of `ostream`.
* To extend it so that it supports your custom class, all you need to do is to write code similar to the following:

</br>

``` c++
std::ostream &operator<<(std::ostream &stream, const MyPair<int, int> &mp){
    stream << mp.firstMember() << ", ";
    stream << mp.secondMember();
    return stream;
}
```

</br>

* Note that our implemetation of `operator<<` is a free(non-member) function.
* You should prefer those to member functions if possible as it actually helps encapsulation.
* If you don't want to provide public access to some field that you wish to print to `ostream`, you can make `operator<<` a friend function, like so:

</br>


``` c++
class MyPair{
    //...
    friend std::ostream &operator<<(std::ostream &stream, const MyPair &mp);
};
std::ostream &operator<<(std::ostream &stream, const MyPair &mp){
    stream << mp.first_ << ", ";
    stream << mp.second_ << ", ";
    stream << mp.secretThirdMember_ << ", ";
    return stream;
}
```

</br>

* Note that this definition of OCP is slightly differenct from the more common one related to polymorphism.
* The latter is about creating base classes that can't be modified themselves, but are open for others to inherit from them.

</br>

### reference: Software Architecture with C++: Design modern systems using effective architecture concepts, design patterns, and techniques with C++20