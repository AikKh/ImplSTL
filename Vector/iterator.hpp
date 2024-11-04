#pragma once

namespace atl
{

template<typename T>
class Iterator {
public:
	using pointer = T*;
    using reference = T&;
    using const_pointer = const T*;
    using const_reference = const T&;

	Iterator(pointer ptr) : m_ptr{ ptr } {}

    const_reference operator*() const
    {
        return *m_ptr;
    }

    const_pointer operator->() const
    {
        return m_ptr;
    }

    reference operator*() 
    {
        return *m_ptr;
    }

    pointer operator->()
    {
        return m_ptr;
    }

    Iterator& operator++()
    {
        ++m_ptr;
        return *this;
    }

    Iterator operator++(int)
    {
        Iterator temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const Iterator& other) const
    {
        return m_ptr == other.m_ptr;
    }

    bool operator!=(const Iterator& other) const
    {
        return !(*this == other);
    }

private:
	pointer m_ptr;
};

}