## Sharing data between threads
* One of the key benefits of using threads for concurrency is the potential to easily and directly share data between them.
* If you are sharing data between threads, you need to have rules for which thread can access which bit of data when, and how any updates are communicated to the other threads that care about that data.
* The ease with which data can be shared between multiple threads in a single process is not only a benefit is can also be a big drawback.
* __Incorrect use of shared data is one of the biggest causes of concurrency-related bugs, and the consequences can be far worse than sausage-flavored cakes.__

</br>

### Problems with shareing data between threads
* The problems with sharing data between threads are all due to the consequences of modifying data.
    * If all shared data is read-only, there's no problem, because the data read by one thread is unaffected by whether or not another thread is reading the same data.
    * But if data is shared between threads, and one or more threads start modifying the data, there's a lot of potential for trouble.
* The simplest potential problem with modifying data that's shared between threads is that of broken invariants.
    * ex) If one thread is reading the doubly linked list while another is removing a node, it's quite possible for the reading thread to see the list with a node only partially removed.(invariant is broken)
    * If the another thread is trying to delete the node, it might end up permanantly corrupting the data structure and eventually crasing the program.
* This is an example of one of the most common causes of bugs in concurrent code: __a race condition__

</br>

### Race conditions
* In concurrency, a race condition is anything where the outcome depends on the relative ordering of execution of operations on two or more threads; the threads race to perform their respective operations.
* When talking about concurrency, the term _race condition_ is usually used to mean a _problematic_ race condition;
    * benign race conditions aren't so interesting and aren't a cause of bugs.
* The standard also defines the term _data race_ to mean the specific type of race condition that arises because of concurrent modification to a single obejct; data races causes the dreaded _undifined behavior._
* Probelmatic race conditions typically occur where completing an operation requires modification of two or more distinct pieces of data.
    * Because the operation must access two seperate pieces of data, these must be modified in sperate instructions, and another thread could potentially access the data structure when only one of them has been completed.
    * Race conditions can often be hard to find and hard to duplicate because the window of opportunity is samll.
    * If the modifications are done as consecutive CPU instructions, the chance of the problem exhibiting on any one run-through is small, even if the data structure is being accessed by another thread concurrently.
* Because race conditions are generally timing-sensitive, they can often disappear entirely when the application is run under the debugger, because the debugger affects the timing of the program, even if only slightly.

</br>

### Avoiding problematic race conditions
* There are several ways to deal with probelmatic race conditions.
* The simplest option is to wrap your data structure with a protection mechanism to ensure that only the thread performing a modification can see the itermediate states where the invariants are broken.
    * From the point of view of ohter threads accessing that data structure, such modifications either haven't started or hav completed.
* Another option is to modify the design of your data structure and its invariants so that modifications are done as a series of indivisible changes, each of which preserves the invariants.
    * This is generally referred to as _lock-free programming_ and is difficult to get right.
    * If you're working at this level, the nuances of the memory model and identifying which threads can potentially see which set of values can get complicated.
* Another way of dealing with race conditions is to handle the updates to the data structures as a _transition_, just as updates to a database are don within a transaction.
    * The required series of data modifications and reads is stored in a transaction log and then committed in a single step.
    * If the commit can't proceed because the data structure has been modified by another thread, the transaction is restarted.
    * This is termed _software transactional memory(STM)_, it's an active research area at the time of writing.
    * It won't be covered in this book, because there's no direct support for STM in C++.
* The most basic mechanism for protecting shared data provided by the C++ Standard is the _mutex_.

</br>

### Protecting shared data with mutexes
* Wouldn't it be nice if you could mark all the pieces of the code that access the data structure as _mutually exclusive_, so that if any thread was running one of them, any other thread that tried to access that data structure had to wait until the first thread was finished?
    * That would make it impossible for a thread to see a broken invariant except when it was the thread doing the modification.
* It's preciesely what you get if you use a synchronization primitive called a _mutex_.
    * Before accessing a shared data structure, you _lock_ the mutex associated with that data, and when you've finished accessing the data structure, you _unlock_ the mutex.
* The Thread Library then ensures that once one thread has locked a specific mutex, all ohter threads that try to lock the same mutex have to wait until the thread that successfully locked the mutex unlocks it.
* Mutexes are __the most general of the data-protection mechanisms available in C++, but they;re not a silver bullet.__
    * It is important to structure your code to protect the right data and avoid race conditions inherent in your interfaces.
    * Mutexes also come with their own problems in the form of _deadlock_ and protecting either too much or too little data.

</br>

### Using mutexes in C++
* In C++, you create a mutex by constructing an instance of _std::mutex_, lock it with call to the _lock()_ member function, and unlock it with a call to the _unlock()_ member function.
* It isn't recommended practice to call the member function directly, because this means that you have to remember to call _unlock()_ on every code path out of a function, including those due to exceptions.
* Instead, the Standard C++ Livrary provides the _std::lock_gurad_ class template, which implements that __RAII__ idiom for a mutex.
    * It locks the supplied mutex on construction and unlocks it on destruction, ensuring a locked mutex is always correctly unlocked.

</br>

[example: 1.protecting a list with a mutex](./1_protecting_list_with_mutex.cc)

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

