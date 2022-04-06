#include <iostream>
#include "../../third_party/GSL/include/gsl/util" // microsoft gsl required
#include <chrono>

using namespace std::chrono;

/*
    We take a timestamp at the start of the function and another one at the end.
    Try running this example and see how uncommenting the throw statement affects the execution.
    In both caes, RAII guard will properly print the execution time
*/
void raii_guard_function() {
    auto timestamp_begin = high_resolution_clock::now();

    auto cleanup = gsl::finally([timestamp_begin] {
    auto timestamp_end = high_resolution_clock::now();
    std::cout << "Execution took: " 
        << duration_cast<microseconds>(timestamp_end - timestamp_begin).count() 
        << " us" << std::endl;
    });

    std::cout << "working section" << std::endl;
    throw std::runtime_error{"Unexpected fault"};
}

int main() 
{
    try{
        raii_guard_function();
    }
    catch(...){

    }
}