#include <iostream>
#include "Graph/graph.hpp"
#include "Graph/adj_list.hpp"
#include "Graph/adj_matrix.hpp"

using namespace atl;

int main()
{
	Graph<AdjMatrix<Directed>> graph{ 6 };

    graph.AddEdge(0, 1);
    graph.AddEdge(0, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(1, 4);
    //graph.AddEdge(2, 4);
    graph.AddEdge(3, 5);
    //graph.AddEdge(4, 3);
    //graph.AddEdge(4, 5);

    //std::cout << graph.DFS([](int n) { std::cout << n << std::endl; });

    //std::cout << std::endl;
    //std::cout << std::endl;

    //std::cout << graph.BFS([](int n) { std::cout << n << std::endl; });

    std::cout << graph.ShortestPath(0, 5) << std::endl;
    std::cout << graph.HasCycle() << std::endl;
    auto sorted = graph.TopoligicalSort();

    std::cout << "Sorted: ";
    for (int i:sorted)
    {
        std::cout << i << ", ";
    }
    std::cout << std::endl;
}
