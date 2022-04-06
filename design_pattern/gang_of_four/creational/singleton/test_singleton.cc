#include "singleton.h"

#include <iostream>

int main()
{
    Singleton &s1 = Singleton::GetInstance();
    Singleton &s2 = Singleton::GetInstance();

    std::cout << s1.GetName() << std::endl;
    std::cout << s2.GetName() << std::endl;

    return 0;
}