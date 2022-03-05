#pragma once

/// <summary>
/// ����ģ��
/// </summary>
template<typename T>
class Singleton
{
public:
    // ����Ĭ�Ϲ���Ϊ���пչ���
    // �ڵ���������Ҳ���ÿչ��캯��
    // �����������粻Ӧ��������󣬱�ֻ֤��һ��ʵ��
    // ͨ����ʽ����Init����ʼ��
    Singleton() = default;
    ~Singleton() = default;

    // ����ȫ���Ŀ����͸�ֵ����
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;

    static T& GetInstance()
    {
        static T instance{};
        return instance;
    }
};

