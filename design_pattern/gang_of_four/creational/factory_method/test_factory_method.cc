#include "factory_method.hpp"

int main()
{
    FactoryObjA factory_a;
    FactoryObjB factory_b;

    auto unique_a = factory_a.CreateFactoryUniquePtr();
    auto unique_b = factory_b.CreateFactoryUniquePtr();
    
    return 0;
}