#pragma once

#include <concepts>
#include <type_traits>

namespace atl
{
    template <typename T>
    concept GraphRepr = requires(T t, int n)
    {
        { T(n) };
        { t.AddEdge(n, n) } -> std::same_as<bool>;
        { t.AddVertex() } -> std::same_as<void>;
        { t.Transpose() } -> std::same_as<void>;
        { t.GetNeighbors(n) };
    };
}

