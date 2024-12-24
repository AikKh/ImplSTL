#pragma once

#include <vector>
#include "iterable.hpp"
#include "direction_repr.hpp"
#include "weighed_adjlist_neighbor_iterator.hpp"

namespace atl
{
    template<typename Direction, typename Weight>
    class AdjList;

    template<>
    class AdjList<void, Unweighted> {
    public:
        AdjList(int node_count) : m_list(node_count) {}

        void AddVertex()
        {
            m_list.push_back({});
        }

        void Transpose()
        {
            decltype(m_list) transposed(m_list.size());

            for (int u = 0; u < m_list.size(); u++)
            {
                for (int v:m_list[u])
                {
                    transposed[v].push_back(u);
                }
            }

            m_list = transposed;
        }

        Iterable<std::vector<int>::const_iterator> GetNeighbors(int n) const
        {
            return Iterable{ m_list[n].begin(), m_list[n].end() };
        }

    protected:
        std::vector<std::vector<int>> m_list;
    };

    template<>
    class AdjList<Directed, Unweighted> : public AdjList<void, Unweighted> {
    public:
        using AdjList<void, Unweighted>::AdjList;

        bool AddEdge(int from, int to)
        {
            if (from >= 0 && from < m_list.size() && to >= 0 && to < m_list.size())
            {
                m_list[from].push_back(to);
                return true;
            }
            return false;
        }
    };

    template<>
    class AdjList<Undirected, Unweighted> : public AdjList<void, Unweighted> {
    public:
        using AdjList<void, Unweighted>::AdjList;

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


    template<>
    class AdjList<void, Weighted> {
    public:
        AdjList(int node_count) : m_list(node_count) {}

        void AddVertex()
        {
            m_list.push_back({});
        }

        void Transpose()
        {
            decltype(m_list) transposed(m_list.size());

            for (int u = 0; u < m_list.size(); u++)
            {
                for (auto [w, v] : m_list[u])
                {
                    transposed[v].push_back(std::make_pair(w, u));
                }
            }

            m_list = transposed;
        }

        Iterable<AdjListNeighborIterator> GetNeighbors(int n) const
        {
            return Iterable{ AdjListNeighborIterator(m_list[n].begin()), AdjListNeighborIterator(m_list[n].end()) };
        }

        Iterable<std::vector<std::pair<int, int>>::const_iterator> GetWeightedNeighbors(int n) const
        {
            return Iterable{ m_list[n].begin(), m_list[n].end() };
        }

    protected:
        std::vector<std::vector <std::pair<int, int>> > m_list;
    };

    template<>
    class AdjList<Directed, Weighted> : public AdjList<void, Weighted> {
    public:
        using AdjList<void, Weighted>::AdjList;

        bool AddEdge(int from, int to, int weight)
        {
            if (from >= 0 && from < m_list.size() && to >= 0 && to < m_list.size())
            {
                m_list[from].push_back(std::make_pair(weight, to));
                return true;
            }
            return false;
        }
    };

    template<>
    class AdjList<Undirected, Weighted> : public AdjList<void, Weighted> {
    public:
        using AdjList<void, Weighted>::AdjList;

        bool AddEdge(int from, int to, int weight)
        {
            if (from >= 0 && from < m_list.size() && to >= 0 && to < m_list.size())
            {
                m_list[from].push_back(std::make_pair(weight, to));
                m_list[to].push_back(std::make_pair(weight, from));
                return true;
            }
            return false;
        }
    };
}