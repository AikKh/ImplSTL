#pragma once

#include <vector>
#include "direction_repr.hpp"

namespace atl
{
    template<typename T>
    class AdjList {
    public:
        AdjList(int node_count) : m_list(node_count) {}

        void AddVertex()
        {
            m_list.push_back({});
        }

        void Transpose()
        {
            std::vector<std::vector<int>> transposed(m_list.size());

            for (int u = 0; u < m_list.size(); u++)
            {
                for (int v : m_list[u])
                {
                    transposed[v].push_back(u);
                }
            }

            m_list = transposed;
        }

        std::pair<std::vector<int>::iterator, std::vector<int>::iterator> GetNeighbors(int n) const
        {
            return std::make_pair(m_list[n].begin(), m_list[n].end());
        }

    protected:
        std::vector<std::vector<int>> m_list;
    };

    template <>
    class AdjList<Directed> : public AdjList<void> {
    public:
        using AdjList<void>::AdjList; 
        using AdjList<void>::Transpose;
        using AdjList<void>::AddVertex;

        bool AddEdge(int from, int to)
        {
            if (from >= 0 && from < m_list.size())
            {
                m_list[from].push_back(to);
                return true;
            }
            return false;
        }
    };

    template <>
    class AdjList<Undirected> : public AdjList<void> {
    public:
        using AdjList<void>::AdjList;
        using AdjList<void>::Transpose;
        using AdjList<void>::AddVertex;

        bool AddEdge(int from, int to)
        {
            if (from >= 0 && from < m_list.size() && to >= 0 && to < m_list.size())
            {
                m_list[from].push_back(to);
                m_list[to].push_back(from);
                return true;
            }
            return false;
        }
    };

}