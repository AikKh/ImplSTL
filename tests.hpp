#pragma once

#include <iostream>

//#define LOG(x) std::cout << x << std::endl
#define LOG(x)

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


static void Test(int number, const std::string& testName, bool result)
{
    std::cout << number << ". " << (result?"[PASS] ":"[FAIL] ") << testName << std::endl;
}

int Tests()
{
    using namespace atl;

    // 1. Test Default Constructor
    {
        Vector<int> v;
        Test(1, "Default Constructor", v.Size() == 0 && v.Capacity() == 0);
    }

    // 2. Test Reserve and Capacity
    {
        Vector<int> v;
        v.Push(1);
        v.Push(2);
        v.Push(3);
        v.Reserve(10);
        Test(2, "Reserve and Capacity", v.Capacity() == 10 && v.Size() == 3);
    }

    // 3. Test Push and Pop
    {
        Vector<int> v;
        v.Push(1);
        v.Push(2);
        int poppedValue = v.Pop();
        Test(3, "Push and Pop", poppedValue == 2 && v.Size() == 1 && v.Back() == 1);
    }

    // 4. Test Initializer List Constructor
    {
        Vector<int> v{ 1, 2, 3 };
        Test(4, "Initializer List Constructor", v.Size() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3);
    }

    // 5. Test Element Access with At() and []
    {
        Vector<int> v{ 1, 2, 3 };
        Test(5, "Element Access At()", v.At(0) == 1 && v.At(1) == 2);
        Test(5, "Element Access []", v[2] == 3);
    }

    // 6. Test Out of Range Exception for At()
    {
        Vector<int> v{ 1, 2, 3 };
        try
        {
            v.At(5);
            Test(6, "Out of Range Exception", false); // Should not reach here
        }
        catch (const std::out_of_range&)
        {
            Test(6, "Out of Range Exception", true);
        }
    }

    // 7. Test Clear
    {
        Vector<int> v{ 1, 2, 3 };
        v.Clear();
        Test(7, "Clear", v.Size() == 0 && v.Capacity() >= 3); // Size should be 0, capacity unchanged
    }

    // 8. Test Empty
    {
        Vector<int> v;
        Test(8, "Empty Vector", v.Empty() == true);
        v.Push(5);
        Test(8, "Non-Empty Vector", v.Empty() == false);
    }

    // 9. Test Copy Assignment
    {
        Vector<int> v1{ 1, 2, 3 };
        Vector<int> v2;
        v2 = v1;
        Test(9, "Copy Assignment", v2.Size() == 3 && v2[0] == 1 && v2[1] == 2 && v2[2] == 3);
    }

    // 10. Test Move Assignment
    {
        Vector<int> v1{ 1, 2, 3 };
        Vector<int> v2;
        v2 = std::move(v1);
        Test(10, "Move Assignment", v2.Size() == 3 && v2[0] == 1 && v2[1] == 2 && v2[2] == 3);
        Test(10, "Move Assignment (v1 size)", v1.Size() == 0); // v1 should be empty after the move
    }

    // 11. Test Iterator Usage
    {
        Vector<int> v{ 1, 2, 3 };
        int sum = 0;
        for (auto it = v.begin(); it != v.end(); ++it)
        {
            sum += *it;
        }
        Test(11, "Iterator", sum == 6);
    }

    // 12. Test Const Iterators
    {
        const Vector<int> v{ 1, 2, 3 };
        int sum = 0;
        for (auto it = v.begin(); it != v.end(); ++it)
        {
            sum += *it;
        }
        Test(12, "Const Iterator", sum == 6);
    }

    // 13. Test Push with Different Type (via Move)
    {
        Vector<A> v;
        v.Push(A{ 1 });
        v.Push(A{ 2 });
        Test(13, "Push Move", v.Size() == 2);
    }

    return 0;
}

