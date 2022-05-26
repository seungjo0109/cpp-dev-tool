#include "observer.hpp"

// Observable class
class Person : public Observalble<Person>
{
public:
    Person(int age): age_(age) {}

    int GetAge() const { return age_; }
    void SetAge(int age){ 
        if(this->age_ == age){
            return;
        }
        else{
            age_ = age;
            Notify(*this, "age"); 
        } 
    }

private:
    int age_;
};


struct ConsolePersonObserver
    : public Observer<Person>
{
private:
    void FieldChanged(Person &source, const std::string &field_name) override
    {
        std::cout << "Person's " << field_name << " has changed to ";
        if(field_name == "age") std::cout << source.GetAge();
        std::cout << "\n";
    }
};

int main()
{
    Person person{10};
    ConsolePersonObserver cpo;
    
    person.Subscribe(cpo);
    person.SetAge(30);
    
    person.Unsubscribe(cpo);
    person.SetAge(20);

    return 0;
}