#pragma once

#include <iostream>

#ifdef NODEBUG
#define LOG(x) std::cout << x << std::endl
#else
#define LOG(x)
#endif

class A {
public:
    A() : m_a{}
    {
        LOG("Default ctor");
    }

    A(int a) : m_a{ a }
    {
        LOG("Param ctor: " << a);
    }

    A(const A& a) : m_a{ a.m_a }
    {
        LOG("Copy ctor");
    }

    A(A&& a) noexcept : m_a{ a.m_a }
    {
        LOG("Move ctor");
    }

    ~A()
    {
        LOG("Dtor");
    }

    A& operator=(const A& a)
    {
        LOG("Copy assign");
        m_a = a.m_a;

        return *this;
    }

    A& operator=(A&& a) noexcept
    {
        LOG("Move assign");
        m_a = a.m_a;

        return *this;
    }

    static friend std::ostream& operator<<(std::ostream& os, const A& a)
    {
        os << "A(" << a.m_a << ")";
        return os;
    }

private:
    int m_a;
};
