## Liskov substitution principle

* The Liskov Substitution Principle(LSP) states that if a function works with a pointer or reference to a base object, it must also work with a pointer or reference to any of its derived objects.
* This rule is sometimes broken because the techniques we apply in source code do not always work in real-world abstractions.
* A famous example is a square and a rectangle. Mathmatically speaking, the former is a specialization of the letter, so there's an `"is a"` relationship from one to the other.

</br>

```c++
class Rectangle
{
public:
    virtual ~Rectangle() = default;
    virtual double area() { return width_ * height_;}
    virtual void setWidth(double width) { width_ = width;}
    virtual void setHeight(double height) {height_ = height;}
private:
    double width_;
    double height_;
};

class Square : public Rectangle
{
public:
    double area() override;
    void setWidth(double width) override;
    void setHeight(double height) override;
};

```

</br>

* How should we implement the members of the `Square` class? If we want to follow the LSP and save the users of such classes from surprises, we can't: our square would stop being a square if we called `setWidth`.
* We can either stop having a square(not expressible using the preceding code) or modify the height as well, thus making the 
square look different than a rectangle.

</br>

* __If your code violates the LSP, it's likely that you're using an incorrect abstraction.__ 
* In our case, `Square` shouldn't inherit from `Rectangle` after all. A better approach could be making the two implement a `GeometricFigure` interface.

</br>

### reference: Software Architecture with C++: Design modern systems using effective architecture concepts, design patterns, and techniques with C++20