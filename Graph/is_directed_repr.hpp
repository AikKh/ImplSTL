#pragma once

#include "adj_list.hpp"
#include "adj_matrix.hpp"
#include "direction_repr.hpp"

namespace atl
{
	template<typename T>
	struct is_directed_graph_representation : std::false_type {};

	template<>
	struct is_directed_graph_representation<atl::AdjMatrix<Directed>> : std::true_type {};

	template<>
	struct is_directed_graph_representation<atl::AdjList<Directed>> : std::true_type {};

	template<typename T>
	inline constexpr bool is_directed_graph_representation_v = is_directed_graph_representation<T>::value;


	template<typename T>
	struct is_undirected_graph_representation : std::false_type {};

	template<>
	struct is_undirected_graph_representation<atl::AdjMatrix<Undirected>> : std::true_type {};

	template<>
	struct is_undirected_graph_representation<atl::AdjList<Undirected>> : std::true_type {};

	template<typename T>
	inline constexpr bool is_undirected_graph_representation_v = is_undirected_graph_representation<T>::value;
}
