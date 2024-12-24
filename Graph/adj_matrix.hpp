#pragma once

#include <vector>
#include "iterable.hpp"
#include "direction_repr.hpp"
#include "weight_repr.hpp"
#include "matrix_neighbor_iterator.hpp"

namespace atl
{
    template<typename Direction, typename Weight>
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

        Iterable<MatrixNeighborIterator> GetNeighbors(int n) const
        {
            MatrixNeighborIterator f(m_matrix[n].begin(), 0, m_matrix.size());
            MatrixNeighborIterator s(m_matrix[n].end(), m_matrix.size(), m_matrix.size());
            return Iterable<MatrixNeighborIterator>(f, s);
        }

        Iterable<std::vector<std::pair<int, int>>::const_iterator> GetWeightedNeighbors(int n) const
        {
            // TODO: write matrix_weighted_neighbor_iterator
            //return Iterable{ m_matrix[n].begin(), m_matrix[n].end() };
        }

    protected:
        std::vector<std::vector<int>> m_matrix;
    };

    template <>
    class AdjMatrix<Directed, Weighted> : public AdjMatrix<void, void> {
    public:
        using AdjMatrix<void, void>::AdjMatrix;

        bool AddEdge(int from, int to, int weight)
        {
            if (from >= 0 && from < m_matrix.size())
            {
                m_matrix[from][to] = weight;
                return true;
            }
            return false;
        }
    };

    template <>
    class AdjMatrix<Undirected, Weighted> : public AdjMatrix<void, void> {
    public:
        using AdjMatrix<void, void>::AdjMatrix;

        bool AddEdge(int from, int to, int weight)
        {
            if (from >= 0 && from < m_matrix.size() && to >= 0 && to < m_matrix.size())
            {
                m_matrix[from][to] = weight;
                m_matrix[to][from] = weight;
                return true;
            }
            return false;
        }
    };

    template <>
    class AdjMatrix<Directed, Unweighted> : public AdjMatrix<Directed, Weighted> {
    public:
        using AdjMatrix<Directed, Weighted>::AdjMatrix;

        bool AddEdge(int from, int to)
        {
            return AdjMatrix<Directed, Weighted>::AddEdge(from, to, 1);
        }
    };

    template <>
    class AdjMatrix<Undirected, Unweighted> : public AdjMatrix<Undirected, Weighted> {
    public:
        using AdjMatrix<Undirected, Weighted>::AdjMatrix;

        bool AddEdge(int from, int to)
        {
            return AdjMatrix<Undirected, Weighted>::AddEdge(from, to, 1);
        }
    };

}

