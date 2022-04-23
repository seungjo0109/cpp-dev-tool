#include <iostream>
#include <memory>

class Object
{
public:
    virtual void PrintObject() = 0;
};

class ObjectA : public Object
{
public:
    virtual void PrintObject() override { std::cout << "I'm ObjectA" << std::endl; }
};

class ObjectB : public Object
{
public:
    virtual void PrintObject() override { std::cout << "I'm ObjectB" << std::endl; }
};

class Factory
{
public:
    enum class Type{
        ObjectA = 1,
        ObjectB = 2,
    };

    virtual std::unique_ptr<Object> CreateFactoryUniquePtr() = 0;
    virtual std::shared_ptr<Object> CreateFactorySharedPtr() = 0;
};

class FactoryObjA : public Factory
{
public:
    virtual std::unique_ptr<Object> CreateFactoryUniquePtr() override
    {
        return std::make_unique<ObjectA>();
    }
    virtual std::shared_ptr<Object> CreateFactorySharedPtr() override
    {
        return std::make_shared<ObjectA>();
    }

    /*
        You can Create additional function
    */
};

class FactoryObjB : public Factory
{
public:
    virtual std::unique_ptr<Object> CreateFactoryUniquePtr() override
    {
        return std::make_unique<ObjectB>();
    }
    virtual std::shared_ptr<Object> CreateFactorySharedPtr() override
    {
        return std::make_shared<ObjectB>();
    }

    /*
        You can Create additional function
    */
};