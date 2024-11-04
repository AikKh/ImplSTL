#pragma once

#include <stack>
#include <memory>
#include "order.hpp"

namespace atl
{

    template<typename T>
    class Iterator {
    public:
        using node = AVLNode<T>;
        using node_ptr = AVLNode<T>*;
        using const_node_ptr = const AVLNode<T>*;
        using node_ref = AVLNode<T>&;
        using const_node_ref = const AVLNode<T>&;

        Iterator(std::unique_ptr<Order<T>> order) : m_order{ std::move(order) } {}

        Iterator& operator++()
        {
            m_order->Next();
            return *this;
        }

        /*Iterator operator++(int)
        {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }*/

        node_ref operator*()
        {
            return *m_order->GetCurrent();
        }

        node_ptr operator->()
        {
            return m_order->GetCurrent();
        }

        const_node_ref operator*() const
        {
            return *m_order->GetCurrent();
        }

        const_node_ptr operator->() const
        {
            return m_order->GetCurrent();
        }

        bool operator==(const Iterator& other) const
        {
            return m_order->GetCurrent() == other.m_order->GetCurrent();
        }

        bool operator!=(const Iterator& other) const
        {
            return !(*this == other);
        }

    private:
        std::unique_ptr<Order<T>> m_order;
    };

}
