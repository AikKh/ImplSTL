#pragma once

#include <vector>
#include <stdexcept>
#include <functional>
#include <queue>
#include <stack>

#include "graph_repr.hpp"
#include "direction_repr.hpp"
#include "weight_repr.hpp"
#include "adj_matrix.hpp"
#include "adj_list.hpp"
#include "graph_type_traits.hpp"

// Questions
// 1. getVerticesAtAGivenLevel: where do I start? In case uses decides, what we do in case if there is no given level?
// 2. SFINAE of member

namespace atl
{
	template<GraphRepr Repr>
	class Graph {
	public:
		Graph(int node_count) : repr{ node_count }, m_size{ node_count }
		{
			assert(node_count > 0, "Node count should be greater then 0");
		}

		bool AddEdge(int src, int dest) requires (is_unweighted_graph_v<Repr>)
		{
			return repr.AddEdge(src, dest);
		}

		bool AddEdge(int src, int dest, int weight) requires (is_weighted_graph_v<Repr>)
		{
			return repr.AddEdge(src, dest, weight);
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

		int ShortestPath(int sorce, int destination) const requires (is_undirected_unweighted_graph_v<Repr>)
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

					for (int v : repr.GetNeighbors(node))
					{
						if (!visited[v])
						{
							visited[v] = true;
							q.push(v);
						}
					}
				}

				++len;
			}
		}

		bool HasCycle() const requires (is_directed_graph_v<Repr>)
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

		bool HasCycle() const requires (is_undirected_graph_v<Repr>)
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

		std::vector<int> TopoligicalSort() const requires (is_directed_graph_v<Repr>)
		{
			std::vector<int> result;
			std::vector<int> in_degree(m_size, 0);
			std::queue<int> q;

			for (int u = 0; u < m_size; u++)
			{
				for (int v : repr.GetNeighbors(u))
				{
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

				for (int v : repr.GetNeighbors(u))
				{
					--in_degree[v];

					if (in_degree[v] == 0)
					{
						q.push(v);
					}
				}
			}

			return result;
		}

		std::vector<std::vector<int>> Tanjan() const requires (is_directed_graph_v<Repr>)
		{
			std::vector<int> ids(m_size, -1);
			std::vector<int> ll(m_size, -1);
			std::vector<bool> on_stack(m_size, false);
			std::stack<int> st;
			std::vector<std::vector<int>> res;

			for (int i = 0; i < m_size; i++)
			{
				if (ids[i] == -1)
				{
					tarjan_impl(i, ids, ll, on_stack, st, res);
				}
			}

			return res;
		}

		std::vector<std::vector<int>> Kosaraju() requires (is_directed_graph_v<Repr>)
		{
			std::vector<bool> visited(m_size, false);
			std::stack<int> st;

			for (int i = 0; i < m_size; i++)
			{
				if (!visited[i])
				{
					fill_order(i, visited, st);
				}
			}

			std::fill(visited.begin(), visited.end(), false);
			Transpose();

			std::vector<std::vector<int>> res;

			while (!st.empty())
			{
				std::vector<int> scc;

				fill_component(st.top(), visited, scc);

				while (!st.empty() && visited[st.top()])
				{
					st.pop();
				}

				res.push_back(std::move(scc));
			}

			Transpose();

			return res;
		}

		int Dijkstra(int src, int dest) const requires (is_weighted_graph_v<Repr>)
		{
			return dijkstra(src, dest);
		}

		int BellmanFord(int src, int dest) const requires (is_directed_weighted_graph_v<Repr>)
		{
			std::vector<int> distances(m_size, std::numeric_limits<int>::max());
			distances[src] = 0;

			for (int i = 0; i < m_size - 1; i++)
			{
				relax(distances);
			}

			return distances[dest];
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

			for (int v : repr.GetNeighbors(node))
			{
				if (has_cycle_directed(v, visited, current))
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

			for (int v : repr.GetNeighbors(node))
			{
				if (v != prev && has_cycle_undirected(v, node, visited))
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

			for (int v:repr.GetNeighbors(node))
			{
				dfs_impl(v, visited, func);
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

				for (int v:repr.GetNeighbors(node))
				{
					if (!visited[v])
					{
						visited[v] = true;
						q.push(v);
					}
				}
			}
		}

		void tarjan_impl(int u, std::vector<int>& ids, std::vector<int>& ll, std::vector<bool>& on_stack, std::stack<int>& st, std::vector<std::vector<int>>& res) const
		{
			static int time = 0;

			ids[u] = ll[u] = time++;
			on_stack[u] = true;
			st.push(u);

			for (int v : repr.GetNeighbors(u))
			{
				if (ids[v] == -1)
				{
					tarjan_impl(v, ids, ll, on_stack, st, res);
					ll[u] = std::min(ll[u], ll[v]);
				}
				else if (on_stack[v] == true)
				{
					ll[u] = std::min(ll[u], ids[v]);
				}
			}

			if (ids[u] == ll[u])
			{
				std::vector<int> scc;

				while (st.top() != u)
				{
					scc.push_back(st.top());
					on_stack[st.top()] = false;
					st.pop();
				}
				scc.push_back(st.top());
				on_stack[st.top()] = false;
				st.pop();

				res.push_back(std::move(scc));
			}
		}
		
		void fill_order(int u, std::vector<bool>& visited, std::stack<int>& st)
		{
			visited[u] = true;

			for (int v:repr.GetNeighbors(u))
			{
				if (!visited[v])
				{
					fill_order(v, visited, st);
				}
			}

			st.push(u);
		}

		void fill_component(int u, std::vector<bool>& visited, std::vector<int>& scc)
		{
			visited[u] = true;
			scc.push_back(u);

			for (int v:repr.GetNeighbors(u))
			{
				if (!visited[v])
				{
					fill_component(v, visited, scc);
				}
			}
		}

		int dijkstra(int src, int dest) const
		{
			auto cmp = [](std::pair<int, int>& a, std::pair<int, int>& b) { return a.first > b.first; };
			std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)> pq;
			std::vector<int> distances(m_size, std::numeric_limits<int>::max());

			pq.push({ 0, src });
			distances[src] = 0;

			while (!pq.empty())
			{
				auto [dist, u] = pq.top();
				pq.pop();

				if (dist > distances[u])
				{
					continue;
				}

				// Does this become Bellman-Ford if we remove this else if?
				else if (u == dest)
				{
					return dist;
				}

				for (auto [w, v] : repr.GetWeightedNeighbors(u))
				{
					if (distances[v] > dist + w)
					{
						distances[v] = dist + w;
						pq.push({ dist + w, v });
					}
				}
			}

			return distances[dest];
		}

		void relax(std::vector<int>& distances) const
		{
			for (int u = 0; u < m_size; u++)
			{
				for (auto [w, v] : repr.GetWeightedNeighbors(u))
				{
					if (distances[v] > distances[u] + w)
					{
						distances[v] = distances[u] + w;
					}
				}
			}
		}

	private:
		Repr repr;
		int m_size;
	};
}

