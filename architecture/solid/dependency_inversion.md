## Dependency inversion principle

* Dependency inversion is a principle useful for decoupling.
* In essence, it means that high-level modules should not depend on lower-level ones. Instead, both should depend on abstractions.
* C++ allows two ways to inverse the dependencies between your classes. The first one is the regular, polymorphic approach and the second uses templates.

</br>

* Assume you're modeling a software development project that is supposed to have frontend and backend developers. A simple approach would be to write it like so:

</br>

``` c++
class FrontEndDeveloper
{
public:
    void developFrontEnd();
private:
};

class BackEndDeveloper
{
public:
    void developBackEnd();
private:
};

class Project
{
public:
    void deliver(){
        fed_.developFrontEnd();
        bed_.developBackEnd();
    }
private:
    FrontEndDeveloper fed_;
    BackEndDeveloper bed_;
};
```

</br>

* Each developer is constructed by the `Project` class. This approach is not ideal, though, since now the higher-level concept, `Project`, depends on lower-level-ones - modules for individual developers.
* Let's see how applying dependency inversion using polymorphism changes this. We can define our developers to depend on interfaces as follows:

</br>

``` c++
class Developer
{
public:
    virtual ~Developer() = default;
    virtual void develop() = 0;
};

class FrontEndDeveloper : public Developer
{
public:
    void develop() override { developFrontEnd(); }
private:
    void developFrontEnd();
};

class BackEndDeveloper : public Developer
{
public:
    void develop() override { developBackEnd(); }
private:
    void developBackEnd();
};

class Project
{
public:
    using Developers = std::vector<std::unique_ptr<Developer>>;
    explicit Project(Developers developers) : developers_(std::move(developers)){

    }
    void deliver(){
        for (auto &developer : developers_){
            developer->develop();
        }
    }
private:
    Developers developers_;
};
```

</br>

* In this approach, `Project` is decoupled from the concrete implementations and instead depends only on the polymorpic interface named `Developer`.
* The "lower-level" concrete classes also depend on this interface. This can help you shorten your build time and allows for much easier unit testing - now you can easily pass mocks as arguments in your test code.

</br>

* Using dependency inversion with virtual dispatch comes at a cost, however, as now we're dealing with memory allocations and the dynamic dispatch has overhead on its own.
* Sometimes C++ compilers can detect that only one implementation is being used for a given interface and will remove the overhead by performing devirtualization.
* Here, however, two implementations are used, so the cost of dynamic dispatch (commonly implemented as jumping through __virtual method tables__, or __vtables__ for short) must be paid.

</br>

* There is another way of inverting dependencies that doesn't have those drawbacks.
* Let's see how this can be done using a variadic template, a generic lambda from C++14, and `variant`, either from C++17 or a third-party library such as Abseil or Boost.

</br>

``` c++
class FrontEndDeveloper
{
public:
    void develop() { developFrontEnd(); }
private:
    void developFrontEnd();
};

class BackEndDeveloper
{
public:
    void develop() { developBackEnd();}
private:
    void developBackEnd();
};

template <typename... Devs>
class Project
{
public:
    using Developers = std::vector<std::variant<Devs...>>;

    explicit Project(Developers developers) 
        : developers_{std::move(developers)} {

    }

    void deliver(){
        for (auto &developer :  developers_){
            std::visit([](auto &dev){dev.develop(); }, developer);
        }
    } 

private:
    Developers developers_;
};
```

</br>

* If you're not familier with `variant`, it's just a class that can hold any the types passed as template parameters.
* Because we're using a variadic template, we can pass however many types we like.
* To call a function on the object stored in the variant, we can either extract it using `std::get` or use `std::visit` and a callable object - in our case, the generic lambda.
* It shows how duck-typing looks in practice. Since all our developer classes implement the `develop` function, the code will compile and run.
* If your developer classes would have different methods, you could, for instance, create a function object that has overloads of `operator()` for different types.

</br>

* This approach is guaranteed to not allocate seperate memory for each developers or use a vitual table.
* However, this approach results in less extensibility, since once the variant is declared, you cannot add another type to it.
* It's about injecting the dependencies through constructor or setters, which can be beneficial to code testability (think about injecting mock objects, for example).
* There are even whole frameworks for injecting dependencies throughout whole applications, such as Boost. DI.

### reference: Software Architecture with C++: Design modern systems using effective architecture concepts, design patterns, and techniques with C++20