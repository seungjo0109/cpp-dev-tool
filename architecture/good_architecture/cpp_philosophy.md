## The philosophy of C++
* C++ is a multi-paradigm language that has benn around for a few decades now. During the years since its inception, it has chenged a lot.
* When C++11 came out, Bjarne Stroustrup, the creator of the language, said that it felt like a completely new language.
* The release of C++20 marks another milestone in the evolution of this beast, bringing a similar revolution to how we write code.
* One thing, however, stayed the same during all those years" the language's philosophy.

</br>

* In short, __it can be summarized by three rules:__
    * There should be no language beneath C++ (except assembly).
    * You only pay for what you use.
    * Offer high-level abstractions at low cost(there's strong ain for zero-cost).

</br>

* Not paying for what you don't use means that, for example, if you want to have your data member created on the stack, you can.
* Many language allocate their objects on the heap, but it's not necessary for C++. Allocating on the heap has come cost to it - probably your allocator will have to lock a mutex for this, which can be a big burden in some types of applications.
* The good part is you can easily allocate variables without dynamically allocating memory each time pretty easily.

</br>

* High-level abstractions are what differentiate C++ from lower-level languages such as C or assembly. They allow for expressing ideas and intent directly in the source code, which plays great with the language's type safety. 

</br>

``` c++
struct Duration{
    int millis_;
};

void example(){
    auto d = Duration{};
    d.millis_ = 100;

    auto timeout = 1; // second
    d.millis_ = timeout; // we meant 1000 millis but assigned just 1
}
```

</br>

* A much better idea would be to leverage the type-safety features offered by the language:

</br>

``` c++
#include <chrono>

using namespace std::literals::chrono_literals;

struct Duration{
    std::chrono::milliseconds millis_;
};

void example(){
    auto d = Duration{};
    // d.millis_ = 100;
    d.millis_ = 100ms;

    auto timeout = 1s;
    d.millis_ = timeout;    // converted automatically to milliseconds
}
```

</br>

* __The prceding abstraction can save us from mistakes and doesn't cost us anything while doing so__; the assembly generated would be the same as for the first example. That's why it's called a zero-cost abstraction.
* Sometimes C++ allows us to use abstractions that actually result in better code than if they were not used.
* One example of a language feature that, when used, could often result in such benefit is coroutines from C++20.

</br>

``` c++
// Approach #1
int count_dots(const char *str, std::size_t len){
    int count = 0;
    for (std::size_t i = 0; i < len; i++){
        if (str[i] == '.') count++;
    }
    return count;
}

// Approach #2
int count_dots(std::string_view str){
    return std::count (std::begin(str), std::end(str), '.');
}
```

</br>

* The second function has a different interface, but even it if was to stay the same, we could just create `std::string_view` from the pointer and the length.
* Since it's such a lightweight type, it should be optimized away by your compiler.

</br>

* Using higher-level abstractions leads to simpler, more maintanable code. The C++ language has strived to provide zero-cost abstractions since its inception, so build upon that instead of redesigning the wheel using lower levels of abstraction.

</br>

### reference: Software Architecture with C++: Design modern systems using effective architecture concepts, design patterns, and techniques with C++20