#pragma once

#include <memory>
#include <string>

class Person
{
class PersonImpl;

public:
    Person(std::string name);
    ~Person();

    void Greet();

    std::unique_ptr<PersonImpl> impl_;
    std::string name_;
};