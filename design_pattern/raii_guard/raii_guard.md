## Automating scope exit actions using RAII guards

* One of the most powerful expressions in C++ is the brace closing a scope.
* RAII guard - an object that, when constructed, will remember what it needs to do when destroyed.
* This way, regardless of whether the scope exits normally or by an exception, the work will happen automatically

</br>

``` c++
// raii_guard.cc

void raii_guard_function() {
    auto timestamp_begin = high_resolution_clock::now();

    auto cleanup = gsl::finally([timestamp_begin] {
    auto timestamp_end = high_resolution_clock::now();
    std::cout << "Execution took: " 
        << duration_cast<microseconds>(timestamp_end - timestamp_begin).count() 
        << " us" << std::endl;
    });

    std::cout << "working section" << std::endl;
    throw std::runtime_error{"Unexpected fault"};
}

```

</br>

### reference: Software Architecture with C++: Design modern systems using effective architecture concepts, design patterns, and techniques with C++20