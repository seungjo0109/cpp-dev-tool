## Interface segregation principle

* The interface segregation principle is just about what its name suggests.
* `No client should be forced to depend on methods that it does not use`
* Firstly, you should prefer more but smaller interfaces to a single big one.
* Secondly, when you're adding a derived class or are extending the functionality of an existing one, __you should think before you extend the interface the class implementations.__

</br>

* Let's show this on an example that violates this principle, starting with the following interface:

</br>

``` c++
// interface
class IFoodProcessor
{
public:
    virtual ~IFoodProcessor() = default;
    virtual void blend() = 0;
};

// implements
class Blender : public IFoodProcessor
{
public:
    void blend() override;
};
```

</br>

* Now we want to model another, mode advanced food processor and we recklessly tried to add more methods to our interface:

``` c++
/*  
    mode advanced food processor(add more methods) 
    Blender class doesn't support this new interface
*/
class IFoodProcessor
{
public:
    virtual ~IFoodProcessor() = default;
    virtual void blend() = 0;
    virtual void slice() = 0;
    virtual void dice() = 0;
};

class AnotherFoodProcessor : public IFoodProcessor 
{
public:
    void blend() override;
    void slice() override;
    void dice() override;
};
```
</br>

* We have an issue with the `Blender` class as it doesn't support this new interface - there's no proper way to implement it.
* Good solution would be to just split the interface into two, each with a seperate responsibility:

</br>

 ``` c++
/*~~~~~~~~~~~~~~~~~~~~~~~~~~
            TO-BE
~~~~~~~~~~~~~~~~~~~~~~~~~~~`*/
class IBlender 
{
public:
    virtual ~IBlender() = default;
    virtual void blend() = 0;
};

class ICutter
{
public:
    virtual ~ICutter() = default;
    virtual void slice() = 0;
    virtual void dice() = 0;
};

class AnotherFoodProcessor : public IBlender, public ICutter
{
public:
    void blend() override {};
    void slice() override {};
    void dice() override {};
};
```

</br>

* Now our `AnotherFoodProcessor` can just implement both interfaces, and we don't need to change the implementation of our existing food processor.