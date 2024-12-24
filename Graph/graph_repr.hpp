#pragma once

#include <concepts>
#include <type_traits>

namespace atl
{
    template <typename T>
    concept GraphRepr = requires(T t, int n)
    {
        { T(n) };                                         // Constructor with node count
        { t.AddVertex() } -> std::same_as<void>;          // Add vertex method
        { t.Transpose() } -> std::same_as<void>;          // Transpose method
        { t.GetNeighbors(n) };                            // Get neighbors method
    } && (
        requires(T t, int src, int dest) { { t.AddEdge(src, dest) } -> std::same_as<bool>; } ||   // Unweighted AddEdge
        requires(T t, int src, int dest, int weight) { { t.AddEdge(src, dest, weight) } -> std::same_as<bool>; }  // Weighted AddEdge
        );
}


