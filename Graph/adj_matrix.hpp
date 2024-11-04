#pragma once

#include <vector>
#include "direction_repr.hpp"
#include "matrix_neighbor_iterator.hpp"

namespace atl
{
    template<typename T>
    class AdjMatrix {
    public:
        AdjMatrix(int node_count) : m_matrix(node_count, std::vector<int>(node_count)) {}

        void AddVertex()
        {
            int size = m_matrix.size();

            for (int i = 0; i < size; i++)
            {
                m_matrix[i].push_back(0);
            }
            m_matrix.push_back(std::vector<int>(size + 1));
        }

        void Transpose()
        {
            int size = m_matrix.size();

            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < i; j++)
                {
                    if (m_matrix[i][j] != m_matrix[j][i])
                    {
                        std::swap(m_matrix[i][j], m_matrix[j][i]);
                    }
                }
            }
        }

        std::pair<NeighborIterator, NeighborIterator> GetNeighbors(int n) const
        {
            NeighborIterator f(m_matrix[n].begin(), 0, m_matrix.size());
            NeighborIterator s(m_matrix[n].end(), m_matrix.size(), m_matrix.size());
            return std::make_pair(f, s);
        }

    protected:
        std::vector<std::vector<int>> m_matrix;
    };

    template <>
    class AdjMatrix<Directed> : public AdjMatrix<void> {
    public:
        using AdjMatrix<void>::AdjMatrix;
        using AdjMatrix<void>::Transpose;
        using AdjMatrix<void>::AddVertex;

        bool AddEdge(int from, int to)
        {
            if (from >= 0 && from < m_matrix.size())
            {
                m_matrix[from][to] = 1;
                return true;
            }
            return false;
        }
    };

    template <>
    class AdjMatrix<Undirected> : public AdjMatrix<void> {
    public:
        using AdjMatrix<void>::AdjMatrix;
        using AdjMatrix<void>::Transpose;
        using AdjMatrix<void>::AddVertex;

        bool AddEdge(int from, int to)
        {
            if (from >= 0 && from < m_matrix.size() && to >= 0 && to < m_matrix.size())
            {
                m_matrix[from][to] = 1;
                m_matrix[to][from] = 1;
                return true;
            }
            return false;
        }
    };

}

