
### Structuring code for protecting shared data
* As you've seen, protecting data with a mutex is not quite as easy as slapping an _std::lock_guard_ object in every member function; one stray pointer or reference, and all that protection is for nothing.
* At one level, checking for stary pointers or reference is easy.
    *  As long as none of the member functions return a pointer or reference to the prtected data to their called either via their return value or via an out parameter, tha data is safe.
    * If you dig a little deeper, it's not that straightfoward - nothing ever is.
    * As well as checking that the member functions don't pass out pointers or references _in_ to functions they call that aren't under your control.
* Particulary dangerous in this regard are functions that are supplied at runtime via a function argument or other means, as in the next listing.

</br>

#### [example: 2.Accidently passing out a reference to protected data](./example/ex2_accidently_passing_out_protected_data.cc)

</br>

* In this example, the code in process_data looks harmless enough, nicely protected with _std::lock_guard_, but the call to the user-supplied _func_ function means that _Foo_ can pass in _MaliciousFunction_ to bypass the protection and then call _DoSomething()_ without the mutex being locked.
* Fundamentally, the problem with this code is that it hasn't done what you set out to do:
    * Mark all the pieces of code that access the data structure as _mutually exclusive_.
    * In this case, it missed the code in _Foo()_ that calls _unprotected->DoSomething()_.
* Unfortunately, this part of the problem isn't something the __C++ Thread Library can help you with; it's up to you as programmers to lock the right mutex to protect your data.__
* On the upside, you have a guideline to follow, which will help you in these cases:
    * _Don't pass pointers and references to protected data outside the scope of the lock, whether by returning them from a function, storing them in externally visible memory, or passing them as arguments to user-supplied functions._
* Although this is a common mistake when trying to use mutexes to proctet shared data, it's far from the only potential pitfall.

</br>
