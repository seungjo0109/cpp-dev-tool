#include "factory.hpp"

int main()
{
    Factory factory;

    auto a_unique = factory.CreateFactoryUniquePtr(Factory::Type::ObjectA);
    auto b_unique = factory.CreateFactoryUniquePtr(Factory::Type::ObjectB);
    // auto c_unique = a_unique;    // compile_error

    a_unique->PrintObject();
    b_unique->PrintObject();

    return 0;
}