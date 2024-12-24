#pragma once

#include <vector>

namespace atl
{
    class AdjListNeighborIterator {
    public:
        using const_iterator = std::vector<std::pair< int, int >>::const_iterator;

        AdjListNeighborIterator(const_iterator iter) : m_iterator{ iter }
        {
        }

        const int& operator*() const
        {
            return (*m_iterator).second;
        }

        const int* operator->() const
        {
            return &(*m_iterator).second;
        }

        AdjListNeighborIterator& operator++()
        {
            ++m_iterator;
            return *this;
        }

        AdjListNeighborIterator operator++(int)
        {
            auto temp = *this;
            ++(*this);
            return temp;
        }

        bool operator!=(const AdjListNeighborIterator& other) const
        {
            return m_iterator != other.m_iterator;
        }

        bool operator==(const AdjListNeighborIterator& other) const
        {
            return m_iterator == other.m_iterator;
        }

    private:
        const_iterator m_iterator;
    };
}

