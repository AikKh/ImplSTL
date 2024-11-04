#pragma once

#include <vector>
#include <stdexcept>
#include <functional>
#include <queue>

#include "graph_repr.hpp"
#include "direction_repr.hpp"
#include "adj_matrix.hpp"
#include "adj_list.hpp"

// 1. Implement Graph DS using adjacency List and Matrix representations.
//    The DS should include the following functionality:
//    Ctor, addEdge, addVertex, transpose, dfs, bfs, getNumComponents(only for undirected Graphs), 
//    getShortestPathFromSrcToDst, getVerticesAtAGivenLevel, getAllPathsFromSrcToDst,
//    hasCycle(2 functions for directed and undirected Graphs), topSort(recursive), Kahn's Algorithm)
//    + Dtor -> if you use "new" operator then try to find a correct way to "delete" nodes.

// 2. Finish both Leetcode problems' lists(Lecture 7 and :sunglasses:

// 3. Find Graph related topics in Cormen and read them. (edited) 

// Questions

// getVerticesAtAGivenLevel: where do I start? In case uses decides, what we do in case if there is no given level?

namespace atl
{
	template<GraphRepr Repr>
	class Graph {
	public:
		Graph(int node_count) : repr{ node_count }, m_size{ node_count }
		{
		}

		bool AddEdge(int src, int dest)
		{
			return repr.AddEdge(src, dest);
		}

		void AddVertex()
		{
			repr.AddVertex();
			++m_size;
		}

		void Transpose()
		{
			repr.Transpose();
		}

		// Returns component count
		int DFS(std::function<void(int)> func) const
		{
			int components = 0;
			std::vector<bool> visited(m_size, false);

			for (int i = 0; i < m_size; i++)
			{
				if (!visited[i])
				{
					dfs_impl(i, visited, func);
					++components;
				}
			}

			return components;
		}

		// Returns component count
		int BFS(std::function<void(int)> func) const
		{
			int components = 0;
			std::vector<bool> visited(m_size, false);

			for (int i = 0; i < m_size; i++)
			{
				if (!visited[i])
				{
					bfs_impl(i, visited, func);
					++components;
				}
			}

			return components;
		}

		int ShortestPath(int sorce, int destination)
		{
			std::queue<int> q;
			std::vector<bool> visited(m_size, false);

			visited[sorce] = true;
			q.push(sorce);

			int len = 0;

			while (!q.empty())
			{
				int size = q.size();

				for (int i = 0; i < size; i++)
				{
					int node = q.front();
					q.pop();

					if (node == destination)
						return len;

					auto [begin, end] = repr.GetNeighbors(node);

					for (; begin != end; ++begin)
					{
						if (!visited[*begin])
						{
							visited[*begin] = true;
							q.push(*begin);
						}
					}
				}

				++len;
			}
		}

		/*template<typename T = Repr, 
			typename std::enable_if_t<std::is_same_v<AdjMatrix<Directed>, T> || std::is_same_v<AdjList<Directed>, T>, int> = 0>*/
		bool HasCycle() const requires (std::is_same_v<AdjMatrix<Directed>, Repr> || std::is_same_v<AdjList<Directed>, Repr>)
		{
			std::vector<bool> visited(m_size, false);
			std::vector<bool> current(m_size, false);

			for (int i = 0; i < m_size; i++)
			{
				if (!visited[i])
				{
					if (has_cycle_directed(i, visited, current))
					{
						return true;
					}
				}
			}

			return false;
		}

		/*template<typename T = Repr, 
			typename std::enable_if_t<std::is_same_v<AdjMatrix<Undirected>, T> || std::is_same_v<AdjList<Undirected>, T>, int> = 0>*/
		bool HasCycle() const requires (std::is_same_v<AdjMatrix<Undirected>, Repr> || std::is_same_v<AdjList<Undirected>, Repr>)
		{
			std::vector<bool> visited(m_size, false);

			for (int i = 0; i < m_size; i++)
			{
				if (!visited[i])
				{
					if (has_cycle_undirected(i, i, visited))
					{
						return true;
					}
				}
			}

			return false;
		}

		std::vector<int> TopoligicalSort() const requires (std::is_same_v<AdjMatrix<Directed>, Repr> || std::is_same_v<AdjList<Directed>, Repr>)
		{
			std::vector<int> result;
			std::vector<int> in_degree(m_size, false);
			std::queue<int> q;

			for (int u = 0; u < m_size; u++)
			{
				auto [begin, end] = repr.GetNeighbors(u);

				for (; begin != end; ++begin)
				{
					int v = *begin;
					++in_degree[v];
				}
			}


			for (int i = 0; i < m_size; i++)
			{
				if (in_degree[i] == 0)
					q.push(i);
			}

			while (!q.empty())
			{
				int u = q.front();
				q.pop();

				result.push_back(u);

				auto [begin, end] = repr.GetNeighbors(u);

				for (; begin != end; ++begin)
				{
					int v = *begin;
					--in_degree[v];

					if (in_degree[v] == 0)
					{
						q.push(v);
					}
				}
			}

			return result;
		}

	private:
		bool has_cycle_directed(int node, std::vector<bool> visited, std::vector<bool> current) const
		{
			if (current[node])
			{
				return true;
			}
			else if (visited[node])
			{
				return false;
			}

			current[node] = true;

			auto [begin, end] = repr.GetNeighbors(node);

			for (; begin != end; ++begin)
			{
				if (has_cycle_directed(*begin, visited, current))
				{
					return true;
				}
			}

			visited[node] = true;
			current[node] = false;

			return false;
		}

		bool has_cycle_undirected(int node, int prev, std::vector<bool> visited) const
		{
			if (visited[node])
			{
				return true;
			}

			visited[node] = true;

			auto [begin, end] = repr.GetNeighbors(node);

			for (; begin != end; ++begin)
			{
				if (*begin != prev && has_cycle_undirected(*begin, node, visited))
				{
					return true;
				}
			}

			return false;
		}

		void dfs_impl(int node, std::vector<bool>& visited, std::function<void(int)>& func) const
		{
			if (visited[node])
				return;

			visited[node] = true;
			func(node);

			auto [begin, end] = repr.GetNeighbors(node);

			for (; begin != end; ++begin)
			{
				dfs_impl(*begin, visited, func);
			}
		}

		void bfs_impl(int node, std::vector<bool>& visited, std::function<void(int)>& func) const
		{
			std::queue<int> q;

			visited[node] = true;
			q.push(node);

			while (!q.empty())
			{
				int node = q.front();
				q.pop();

				func(node);

				auto [begin, end] = repr.GetNeighbors(node);

				for (; begin != end; ++begin)
				{
					if (!visited[*begin])
					{
						visited[*begin] = true;
						q.push(*begin);
					}
				}
			}
		}

	private:
		Repr repr;
		int m_size;
	};
}

