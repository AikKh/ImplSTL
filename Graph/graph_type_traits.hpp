#pragma once

#include "adj_list.hpp"
#include "adj_matrix.hpp"
#include "direction_repr.hpp"
#include <type_traits>

namespace atl
{
    template<typename T, typename Direction, typename Weight>
    struct is_graph_type : std::false_type {};

#define DEFINE_GRAPH_TYPE(matrix_or_list, direction, weight) \
    template<> struct is_graph_type<atl::matrix_or_list<direction, weight>, direction, weight> : std::true_type {};

    DEFINE_GRAPH_TYPE(AdjMatrix, Directed, Unweighted)
    DEFINE_GRAPH_TYPE(AdjList, Directed, Unweighted)
    DEFINE_GRAPH_TYPE(AdjMatrix, Undirected, Unweighted)
    DEFINE_GRAPH_TYPE(AdjList, Undirected, Unweighted)
    DEFINE_GRAPH_TYPE(AdjMatrix, Directed, Weighted)
    DEFINE_GRAPH_TYPE(AdjList, Directed, Weighted)
    DEFINE_GRAPH_TYPE(AdjMatrix, Undirected, Weighted)
    DEFINE_GRAPH_TYPE(AdjList, Undirected, Weighted)

#undef DEFINE_GRAPH_TYPE

#define DEFINE_GRAPH_TRAIT(trait_name, direction, weight) \
        template<typename T> inline constexpr bool trait_name##_v = is_graph_type<T, direction, weight>::value;

    DEFINE_GRAPH_TRAIT(is_directed_unweighted_graph, Directed, Unweighted)
    DEFINE_GRAPH_TRAIT(is_undirected_unweighted_graph, Undirected, Unweighted)
    DEFINE_GRAPH_TRAIT(is_directed_weighted_graph, Directed, Weighted)
    DEFINE_GRAPH_TRAIT(is_undirected_weighted_graph, Undirected, Weighted)

#undef DEFINE_GRAPH_TRAIT

#define DEFINE_COMBINED_TRAIT(trait_name, cond1, cond2) \
        template<typename T> inline constexpr bool trait_name##_v = cond1##_v<T> || cond2##_v<T>;

    DEFINE_COMBINED_TRAIT(is_directed_graph, is_directed_unweighted_graph, is_directed_weighted_graph)
    DEFINE_COMBINED_TRAIT(is_undirected_graph, is_undirected_unweighted_graph, is_undirected_weighted_graph)
    DEFINE_COMBINED_TRAIT(is_weighted_graph, is_directed_weighted_graph, is_undirected_weighted_graph)
    DEFINE_COMBINED_TRAIT(is_unweighted_graph, is_directed_unweighted_graph, is_undirected_unweighted_graph)

#undef DEFINE_COMBINED_TRAIT

}
