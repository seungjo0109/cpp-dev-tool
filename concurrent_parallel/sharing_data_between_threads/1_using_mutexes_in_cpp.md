
### Using mutexes in C++
* In C++, you create a mutex by constructing an instance of _std::mutex_, lock it with call to the _lock()_ member function, and unlock it with a call to the _unlock()_ member function.
* It isn't recommended practice to call the member function directly, because this means that you have to remember to call _unlock()_ on every code path out of a function, including those due to exceptions.
* Instead, the Standard C++ Livrary provides the _std::lock_gurad_ class template, which implements that __RAII__ idiom for a mutex.
    * It locks the supplied mutex on construction and unlocks it on destruction, ensuring a locked mutex is always correctly unlocked.

</br>

#### [example: 1.protecting a list with a mutex](./example/ex1_protecting_list_with_mutex.cc)

</br>

* C++17 also introduces an enhanced version of lock guard called _std::scoped_lock_, so in a C++17 environment, this may well be written as

``` c++
    std::scoped_lock guard(some_mutex);
```

</br>

* Although there are occasions where this use of global variables is appropriate, in the majority of cases it's common to group the mutex and the protected data together in a class rather than use global variables.
* This is a standard application of object-oriented design rules: by putting them in a class, you're clearly marking the, as related, and you can encapsulate the functionality and enforce the protection.
* If all the member functions of the class lock the mutex before accessing any other data members and unlock it when done, the data is nicely protected from all comers.
    * Well, __that's not quite true,__ as the asture among you will have noticed: if one of the member functions returns a pointer of reference to the protected data, then it doesn't matter that the member functions all lcok the mutex in a nice, orderly fasion, because you've blown a big hole in the protection.
    * _Any code that has access to that pointer or reference can now access(and potentially modify) the protected data without locking the mutex._
* Protecting data with a mutex therefore requires careful interface design to ensure that the mutex is locked before there's any access to the protected data and thet there are no backdoors.

</br>