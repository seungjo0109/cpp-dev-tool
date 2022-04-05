#pragma once

#include <iostream>

class Singleton
{
public:
    static Singleton& GetInstance()
    {
        static Singleton instance;  //thread-safe
        return instance;
    }
    const char* GetName(){ return name_; }

private:
    Singleton(){ name_ = "singleton";}
    Singleton(const Singleton&){}
    Singleton& operator=(const Singleton&){}
    ~Singleton(){}

    const char* name_;
};