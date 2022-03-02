#pragma once

template<typename T>
class Singleton
{
public:
    Singleton() { }
    ~Singleton() { };

private:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static T& GetInstance()
    {
        static T instance;
        return instance;
    }
};

