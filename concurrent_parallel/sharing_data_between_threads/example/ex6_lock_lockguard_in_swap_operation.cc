#include <mutex>

class some_big_object;

void swap(some_big_object& lhs, some_big_object& rhs);

class X
{
public:
    X(some_big_object const& sd): some_detail_(sd) {}

    friend void swap(X& lhs, X& rhs)
    {
        if(&lhs == &rhs){
            return;
        }
        std::lock(lhs.m_, rhs.m_);
        std::lock_guard<std::mutex> lock_a(lhs.m_, std::adopt_lock);
        std::lock_guard<std::mutex> lock_b(rhs.m_, std::adopt_lock);
        swap(lhs.some_detail_, rhs.some_detail_);

        /* std::scoped_lock */
        // std::scoped_lock guard(lhs.m_, rhs.m_);
        // swap(lhs.some_detail_, rhs.some_detail_);
    }

private:
    some_big_object some_detail_;
    std::mutex m_;
};