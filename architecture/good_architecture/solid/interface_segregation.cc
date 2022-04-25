#include <iostream>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~
            AS-IS
~~~~~~~~~~~~~~~~~~~~~~~~~~~`*/
// interface
// class IFoodProcessor
// {
// public:
//     virtual ~IFoodProcessor() = default;
//     virtual void blend() = 0;
// };

// implements
// class Blender : public IFoodProcessor
// {
// public:
//     void blend() override;
// };

/*  
    mode advanced food processor(add more methods) 
    Blender class doesn't support this new interface
*/
// class IFoodProcessor
// {
// public:
//     virtual ~IFoodProcessor() = default;
//     virtual void blend() = 0;
//     virtual void slice() = 0;
//     virtual void dice() = 0;
// };

// class AnotherFoodProcessor : public IFoodProcessor 
// {
// public:
//     void blend() override;
//     void slice() override;
//     void dice() override;
// };

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