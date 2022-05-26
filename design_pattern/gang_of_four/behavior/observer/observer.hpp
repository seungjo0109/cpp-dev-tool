#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Observer class
template <typename T>
class Observer
{
public:
    virtual void FieldChanged(
        T& source,
        const std::string& field_name
    ) = 0;
};

// Observable interface
template<typename T>
class Observalble
{
public:
    void Notify(T& source, const std::string& field_name)
    {
        for(auto observer : observers_){
            observer->FieldChanged(source, field_name);
        }
    }

    void Subscribe(Observer<T>& observer)
    {
        observers_.push_back(&observer);
    }

    void Unsubscribe(Observer<T>& observer)
    {
        observers_.erase(
            remove(observers_.begin(), observers_.end(), &observer),
            observers_.end()
        );
    }

private:
    std::vector<Observer<T>*> observers_;
};
