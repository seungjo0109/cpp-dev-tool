#include <iostream>

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

/* 
    this class violates LSP 
    Square is a Rectangle?
*/
class Square : public Rectangle
{
public:
    double area() override { 
        //return with_ * width_;
        //return height_ * height_;
        return width_ * height_;
    }
    void setWidth(double width) override{
        //height_ = height;
        width_ = width;
    }
    void setHeight(double height) override{
        // width_ = height;
        height_ = height;
    }
private:
    double width_;
    double height_;
};

int main()
{
    Square square;

    square.setWidth(10);
    square.setHeight(11);

    std::cout << "square area is " << square.area() << std::endl;
    std::cout << "violates LSP, this is not a square" << std::endl;

    return 0;
}