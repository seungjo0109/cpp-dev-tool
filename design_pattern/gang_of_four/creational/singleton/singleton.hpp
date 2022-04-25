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
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    ~Singleton(){}

    const char* name_;
};