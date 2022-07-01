/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    https://www.cppstories.com/2020/07/lambdas5ex.html/
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

// 5. Returning a lambda
std::function<int(int)> CreateLambda(int y){
    return [&y](int x) {return x+y;};
}

int main()
{
    /* 1. Recursive lambda */
    // std::function
    // need to capture factorial and then we can refer to it inside the lambda body.
    const std::function<int(int)> factorial = [&factorial](int n){
        return n > 1 ? n * factorial(n-1) : 1;
    };
    std::cout << "Recursive factorial lambda function(use std::function)\n"; 
    std::cout << "factorial(5): " << factorial(5) << "\n\n";

    // generic lambdas
    // This time it’s even more complicated (but doesn’t require heavy use of std::function). 
    // It uses internal lambda for the main computation and then it’s passed as a generic argument.
    const auto factorial_generic = [](int n){
        const auto fact_impl = [](int n, const auto& impl)->int{
            return n > 1 ? n*impl(n-1, impl) : 1;
        };
        return fact_impl(n, fact_impl);
    };
    std::cout << "Recursive factorial lambda function(use generic lambda)\n"; 
    std::cout << "factorial(5): " << factorial_generic(5) << std::endl;

    /* 2. constexpr lambda */
    // Since C++17 we can write lambdas that have the call operator defined as constexpr
    constexpr auto factorial_constexpr = [](int n){
        constexpr auto fact_impl = [](int n, const auto& impl)->int{
            return n > 1 ? n * impl(n - 1, impl) : 1;
        };
        return fact_impl(n, fact_impl);
    };
    std::cout << "constexpr factorial lambda function\n"; 
    std::cout << "factorial(5): " << factorial_constexpr(5) << "\n\n";

    /* 3. Storing lambdas in a container */
    // This might be a bit cheating… but we can theoretically store lambdas in a container.
    std::vector<std::function<std::string(const std::string&)>> vec_filters;

    vec_filters.emplace_back([](const std::string& x){
        return x + "lambdas ";
    });
    vec_filters.emplace_back([](const std::string& x){
        return x + "in a ";
    });
    vec_filters.emplace_back([](const std::string& x){
        return x + "containers";
    });

    std::string str = "Storing ";
    for(auto &entry_func : vec_filters){
        str = entry_func(str);
    }
    std::cout << "Print lambdas in vector: " << str << "\n\n";

    /* 4. Generic lambdas and help with deduction */
    // C++14 brought an important addition to lambdas: generic lambda arguments. 
    const std::map<std::string, int> numbers {
        { "one", 1 }, {"two", 2 }, { "three", 3 }
    };

    std::for_each(std::begin(numbers), std::end(numbers), [](const auto& entry) {
        std::cout << entry.first << " = " << entry.second << '\n';
    });

    /* 5. Returning a lambda */
    auto ret_lambda = CreateLambda(10);
    std::cout << "\nReturning lambda function test: ret_lambda(20): " << ret_lambda(20) << "\n";

    return 0;

}