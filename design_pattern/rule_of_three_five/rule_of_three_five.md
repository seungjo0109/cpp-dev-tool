## Adhreing to the rules of three and five

* There's one more thing to mention when discussing special member functions
* If you don't delete them and are poviding your own implementations, most probably you need to define all of them, including the destructor, too
* This was called the rule of three in C++98(due to the need to define three functions: the copy constructor, the copy assignment operator, and the destructor)
* Since C++11's move operations, it is now replaced by the rule of five(the two additional ones being the move constructor and the move assignment operator)
* Applying these rules can help you avoid resource management issues.

</br>

### Adhering to the rule of zero
* If, on the other hand, you're good to go with just the defualt implementations of all special member functions, then just don't declare them at all.
* This is a clear sign that you want the default behavior. It's also the least confusing.

</br>

``` c++
// rule_of_three_five.cc

class PotentiallyMisleading   // this class also not movable
{
public:
    PotentiallyMisleading() = defualt;
    Potentially
    
};
```

</br>

* Even though we defaulted all the members, the class is still non-copyable. That's because if has a `unique_ptr` member that is non-copyable itself.
* A better approach would be to apply the rule of zero and instead write the follwing:

</br>

``` c++
class RuleOfZero {
    std::unique_ptr<int> int_;
}
```

</br>


* Now we have less boilerplate code and by looking at the members, it's easier to notice that it does not support copying
* There's one more important idiom to know about when it comes to copying that you'll get to know in a minute.

</br>


### reference: Software Architecture with C++: Design modern systems using effective architecture concepts, design patterns, and techniques with C++20