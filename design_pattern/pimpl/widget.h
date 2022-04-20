#include <iostream>
#include <memory>
#include <experimental/propagate_const>

class Widget
{
public:
    void Draw() const;
    void Draw();
    bool Shown() const {return true;}

    Widget() = default;
    explicit Widget(int n) : pimpl_{std::make_unique<Impl>(n)} {}
    Widget(Widget&&) = default;
    ~Widget() = default;
    Widget& operator=(const Widget&) = delete;
    Widget& operator=(Widget&&) = default;

private:
    class Impl;
    std::experimental::propagate_const<std::unique_ptr<Impl>> pimpl_;
};

class Widget::Impl
{
public:
    void Draw(const Widget& widget) const
    {
        if(widget.Shown()){
            std::cout << "Drawing const widget, n_: " << n_ << std::endl;
        }
    }
    void Draw(Widget& widget)
    {
        if(widget.Shown()){
            std::cout << "Drawing non-const widget, n_: " << n_ << std::endl;
        }    
    }

    Impl(int n): n_(n) {}

private:
    int n_;
};