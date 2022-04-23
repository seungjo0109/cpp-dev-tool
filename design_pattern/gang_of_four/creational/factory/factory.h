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

    std::unique_ptr<Object> CreateFactoryUniquePtr(Factory::Type type)
    {
        if(type == Type::ObjectA){
            return std::make_unique<ObjectA>();
        }
        else if(type == Type::ObjectB){
            return std::make_unique<ObjectB>();
        }
    }

    std::shared_ptr<Object> CreateFactorySharedPtr(Factory::Type type)
    {
        if(type == Type::ObjectA){
            return std::make_shared<ObjectA>();
        }
        else if(type == Type::ObjectB){
            return std::make_shared<ObjectB>();
        }
    }
};