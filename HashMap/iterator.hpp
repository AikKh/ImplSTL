#pragma once

#include "node.hpp"
#include <utility>

namespace atl
{

    template<typename Key, typename T>
    class Iterator {
    public:
        using key_type = Key;
        using value_type = T;
        using pair_type = std::pair<const Key, T>;
        using node = Node<pair_type>;

        Iterator(node** data, int size) : m_data{ data }, m_node{ nullptr }, m_size{ size }, m_curr{ 0 }
        {
            if (m_data)
            {
                if (!m_data[m_curr])
                    GetNextChain();

                m_node = m_data[m_curr];
            }
        }

        const pair_type& operator*() const
        {
            return m_node->value;
        }

        const pair_type* operator->() const
        {
            return &m_node->value;
        }

        pair_type& operator*()
        {
            return m_node->value;
        }

        pair_type* operator->()
        {
            return &m_node->value;
        }

        Iterator& operator++()
        {
            if (m_node && m_node->next)
            {
                m_node = m_node->next;
                return *this;
            }

            GetNextChain();

            if (m_curr < m_size)
            {
                m_node = m_data[m_curr];
            }
            else
            {
                m_node = nullptr;
            }


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
            return m_node == other.m_node;
        }

        bool operator!=(const Iterator& other) const
        {
            return !(*this == other);
        }

    private:
        void GetNextChain()
        {
            ++m_curr;
            while (m_curr <= m_size && !m_data[m_curr])
            {
                ++m_curr;
            }
        }

    private:
        node** m_data;
        node* m_node;
        int m_size;
        int m_curr;
    };

}