#pragma once

#include <utility>

namespace atl
{
	template<typename T>
	struct Node {
	public:
		Node(T val, Node<T>* nxt = nullptr) : value{ std::move(val) }, next{ nxt } {}

		T value;
		Node<T>* next;
	};
}