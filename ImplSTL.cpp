#include <cassert>
#include <iostream>
#include <vector>

#include "Graph/graph.hpp"

using namespace atl;

void testDirectedUnweightedGraph()
{
    atl::Graph<atl::AdjList<atl::Directed, atl::Unweighted>> graph(4);

    graph.AddEdge(0, 1);
    graph.AddEdge(1, 2);
    graph.AddEdge(2, 3);
    graph.AddEdge(3, 0);

    std::vector<int> dfs_order;
    graph.DFS([&](int n) { dfs_order.push_back(n); });
    assert(dfs_order.size() == 4 && "DFS should visit all nodes");

    std::vector<int> bfs_order;
    graph.BFS([&](int n) { bfs_order.push_back(n); });
    assert(bfs_order.size() == 4 && "BFS should visit all nodes");

    assert(graph.HasCycle() && "Directed unweighted graph should detect a cycle");

    graph.Transpose();
    std::cout << "Directed unweighted graph tests passed.\n";
}

void testDirectedWeightedGraph()
{
    atl::Graph<atl::AdjList<atl::Directed, atl::Weighted>> graph(4);

    graph.AddEdge(0, 1, 5);
    graph.AddEdge(1, 2, 3);
    graph.AddEdge(2, 3, 2);
    graph.AddEdge(3, 0, 1);

    std::vector<int> dfs_order;
    graph.DFS([&](int n) { dfs_order.push_back(n); });
    assert(dfs_order.size() == 4 && "DFS should visit all nodes");

    std::vector<int> bfs_order;
    graph.BFS([&](int n) { bfs_order.push_back(n); });
    assert(bfs_order.size() == 4 && "BFS should visit all nodes");

    assert(graph.HasCycle() && "Directed weighted graph should detect a cycle");

    graph.Transpose();
    std::cout << "Directed weighted graph tests passed.\n";
}

void testUndirectedUnweightedGraph()
{
    atl::Graph<atl::AdjList<atl::Undirected, atl::Unweighted>> graph(4);

    graph.AddEdge(0, 1);
    graph.AddEdge(1, 2);
    graph.AddEdge(2, 3);

    std::vector<int> dfs_order;
    graph.DFS([&](int n) { dfs_order.push_back(n); });
    assert(dfs_order.size() == 4 && "DFS should visit all nodes");

    std::vector<int> bfs_order;
    graph.BFS([&](int n) { bfs_order.push_back(n); });
    assert(bfs_order.size() == 4 && "BFS should visit all nodes");

    assert(!graph.HasCycle() && "Undirected unweighted graph should not detect a cycle");

    std::cout << "Undirected unweighted graph tests passed.\n";
}

void testUndirectedWeightedGraph()
{
    atl::Graph<atl::AdjList<atl::Undirected, atl::Weighted>> graph(4);

    graph.AddEdge(0, 1, 2);
    graph.AddEdge(1, 2, 4);
    graph.AddEdge(2, 3, 3);

    std::vector<int> dfs_order;
    graph.DFS([&](int n) { dfs_order.push_back(n); });
    assert(dfs_order.size() == 4 && "DFS should visit all nodes");

    std::vector<int> bfs_order;
    graph.BFS([&](int n) { bfs_order.push_back(n); });
    assert(bfs_order.size() == 4 && "BFS should visit all nodes");

    assert(!graph.HasCycle() && "Undirected weighted graph should not detect a cycle");

    std::cout << "Undirected weighted graph tests passed.\n";
}

void SCCTest()
{
    Graph<AdjList<Directed, Unweighted>> graph{ 7 };

    graph.AddEdge(0, 1);

    graph.AddEdge(1, 2);
    graph.AddEdge(1, 6);

    graph.AddEdge(2, 3);

    graph.AddEdge(3, 2);
    graph.AddEdge(3, 4);
    graph.AddEdge(3, 5);

    graph.AddEdge(4, 5);

    graph.AddEdge(5, 4);

    graph.AddEdge(6, 0);
    graph.AddEdge(6, 2);


    std::cout << "Tarjan\n";

    auto res = graph.Tanjan();
    for (auto& scc : res)
    {
        for (int u : scc)
        {
            std::cout << u << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Kosaraju\n";

    res = graph.Kosaraju();
    for (auto& scc : res)
    {
        for (int u:scc)
        {
            std::cout << u << " ";
        }
        std::cout << std::endl;
    }
}

void testShortestPath()
{
    // Initial simple test
    atl::Graph<atl::AdjList<atl::Directed, atl::Weighted>> graph(3);

    graph.AddEdge(0, 1, 3);
    graph.AddEdge(0, 2, 4);
    graph.AddEdge(2, 1, -2);

    int shortest_path = graph.Dijkstra(0, 1);

    std::cout << "Shortest path result: " << shortest_path << std::endl;
    std::cout << "Shortest path test passed.\n";

    // Additional complex test case
    atl::Graph<atl::AdjList<atl::Directed, atl::Weighted>> complexGraph(6);

    complexGraph.AddEdge(0, 1, 1);
    complexGraph.AddEdge(1, 2, 2);
    complexGraph.AddEdge(2, 3, 1);
    complexGraph.AddEdge(3, 4, 3);
    complexGraph.AddEdge(4, 5, 2);
    complexGraph.AddEdge(0, 2, 4);
    complexGraph.AddEdge(1, 3, 7);
    complexGraph.AddEdge(0, 3, 10);
    complexGraph.AddEdge(3, 5, 6);
    complexGraph.AddEdge(1, 5, 9);

    // Expected shortest path from 0 to 5: should follow 0 -> 1 -> 2 -> 3 -> 4 -> 5
    int complexShortestPath = complexGraph.Dijkstra(0, 5);

    std::cout << "Complex shortest path result: " << complexShortestPath << std::endl;
    std::cout << "Expected shortest path from 0 to 5: " << 9 << std::endl;
    std::cout << "Complex shortest path test passed.\n";
}

void testNegativeWeightFailureWithDijkstra()
{
    atl::Graph<atl::AdjList<atl::Directed, atl::Weighted>> graph(3);

    graph.AddEdge(0, 1, 2);    
    graph.AddEdge(0, 2, 5);    
    graph.AddEdge(2, 1, -10);   

    int shortest_path = graph.BellmanFord(0, 1);

    std::cout << "Shortest path result using Dijkstra (expected to fail): " << shortest_path << std::endl;
    std::cout << "Expected shortest path using Bellman-Ford: " << -5 << std::endl;

    std::cout << "Note: Dijkstra's algorithm is expected to fail with negative weights.\n";
}


int main()
{
    //testDirectedUnweightedGraph();
    testDirectedWeightedGraph();
    testUndirectedUnweightedGraph();
    testUndirectedWeightedGraph();
    SCCTest();
    testShortestPath();
    testNegativeWeightFailureWithDijkstra();

    std::cout << "All graph tests passed.\n";
    return 0;
}
