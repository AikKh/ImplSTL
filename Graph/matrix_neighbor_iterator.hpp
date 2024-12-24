#pragma once

#include <vector>

namespace atl
{
    class MatrixNeighborIterator {
    public:
        using iterator = std::vector<int>::iterator;
        using const_iterator = std::vector<int>::const_iterator;
        using reference = std::vector<int>::reference;
        using pointer = std::vector<int>::pointer;
        using const_reference = std::vector<int>::const_reference;
        using const_pointer = std::vector<int>::const_pointer;

        MatrixNeighborIterator(const_iterator ptr, int start, int size) : m_ptr{ ptr }, m_index{ start }, m_size{ size }
        {
            SkipZeros();
        }

        reference operator*()
        {
            return m_index;
        }

        pointer operator->()
        {
            return &m_index;
        }

        const_reference operator*() const
        {
            return m_index;
        }

        const_pointer operator->() const
        {
            return &m_index;
        }

        MatrixNeighborIterator& operator++()
        {
            ++m_index;
            SkipZeros();
            return *this;
        }

        MatrixNeighborIterator operator++(int)
        {
            MatrixNeighborIterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator!=(const MatrixNeighborIterator& other) const
        {
            return m_index != other.m_index;
        }

        bool operator==(const MatrixNeighborIterator& other) const
        {
            return m_index == other.m_index;
        }

    private:
        void SkipZeros()
        {
            while (m_index < m_size && m_ptr[m_index] == 0) ++m_index;
        }

    private:
        const_iterator m_ptr;
        int m_index;
        int m_size;
    };
}

