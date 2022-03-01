#pragma once

class Singleton
{
private:
    Singleton() { }
    ~Singleton() { };

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static Singleton& GetInstance()
    {
        static Singleton instance;
        return instance;
    }
};

