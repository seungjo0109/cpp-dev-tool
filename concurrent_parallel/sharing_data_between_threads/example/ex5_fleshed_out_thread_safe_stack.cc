#include <exception>
#include <memory>
#include <mutex>
#include <stack>

struct empty_stack : std::exception
{
    const char* what() const throw();
};

template<typename T>
class threadsafe_stack
{
public:
    threadsafe_stack() {}
    threadsafe_stack(const threadsafe_stack& other)
    {
        std::lock_guard<std::mutex> lg(other.m_);
        data = other.data;      // Copy performed in constructor body
    }
    threadsafe_stack& operator=(const threadsafe_stack&) = delete;

    void push(T value){
        std::lock_guard<std::mutex> lg(m_);
        data.push(std::move(value));
    }

    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex> lg(m_);
        if(data_.empty()){
            throw empty_stack();
        }
        std::shared_ptr<T> const res(std::make_shared<T>(data_.top()));
        data_.pop();
    }

    void pop(T& value)
    {
        std::lock_guard<std::mutex> lg(m_);
        if(data.empty()){
            throw empty_stack();
        }
        value = data_.top();
        data_.pop();
    }    

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(m_);
        return data_.empty();
    }

private:
    std::stack<T> data_;
    mutable std::mutex m_;
};