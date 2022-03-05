#pragma once

/// <summary>
/// 单例模板
/// </summary>
template<typename T>
class Singleton
{
public:
    // 保留默认构造为公有空构造
    // 在单例子类中也设置空构造函数
    // 除子类外的外界不应当构造对象，保证只有一个实例
    // 通过显式调用Init来初始化
    Singleton() = default;
    ~Singleton() = default;

    // 禁用全部的拷贝和赋值函数
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;

    static T& GetInstance()
    {
        static T instance{};
        return instance;
    }
};

