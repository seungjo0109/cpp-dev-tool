#include <iostream>

#include "person.hpp"

/*
    Pimpl idiom is that all of the details go into the cpp file.
    Pimpl idiom can improve compilation speed.
*/

class Person::PersonImpl
{
public:
    void Greet(Person& person);
private:
    /* You can hide secret section by using Pimpl idiom */
};

void Person::PersonImpl::Greet(Person& person)
{
    std::cout << "person's name is " << person.name_ << std::endl;
}

Person::Person(std::string name)
    : impl_(std::make_unique<PersonImpl>()), name_(name)
{

}

Person::~Person()
{

}

void Person::Greet()
{
    impl_->Greet(*this);
}

/* Test section */
int main()
{
    Person person("test_user");

    person.Greet();

    return 0;
}
