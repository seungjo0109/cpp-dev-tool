#include <exception>
#include <memory>

struct empty_stack: std::exception
{
    const char* what() const noexcept;
};

template<typename T>
class threadsafe_stack
{
public:
    threadsafe_stack();
    threadsafe_stack(const threadsafe_stack&);
    threadsafe_stack& operator=(const threadsafe_stack&) = delete;     // assignment operator is deleted
    void push(T value);
    std::shared_ptr<T> pop();
    void pop(T& value);
    bool empty() const;
};