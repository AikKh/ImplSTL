#pragma once

#include <memory>

#include "iterator.hpp"
#include "Orders/inorder.hpp"
#include "Orders/preorder.hpp"
#include "Orders/postorder.hpp"

namespace atl
{

template<typename T>
class InorderIterable {
public:
	InorderIterable(AVLNode<T>* node) : m_node{ node } {}
	
	Iterator<T> begin()
	{
		return Iterator<T>{ std::make_unique<Inorder<T>>(m_node) };
	}

	Iterator<T> end()
	{
		return Iterator<T>{ std::make_unique<Inorder<T>>(nullptr) };
	}

private:
	AVLNode<T>* m_node;
};

template<typename T>
class PreorderIterable {
public:
	PreorderIterable(AVLNode<T>* node) : m_node{ node } {}

	Iterator<T> begin()
	{
		return Iterator<T>{ std::make_unique<Preorder<T>>(m_node) };
	}

	Iterator<T> end()
	{
		return Iterator<T>{ std::make_unique<Preorder<T>>(nullptr) };
	}

private:
	AVLNode<T>* m_node;
};

template<typename T>
class PostorderIterable {
public:
	PostorderIterable(AVLNode<T>* node) : m_node{ node } {}

	Iterator<T> begin()
	{
		return Iterator<T>{ std::make_unique<Postorder<T>>(m_node) };
	}

	Iterator<T> end()
	{
		return Iterator<T>{ std::make_unique<Postorder<T>>(nullptr) };
	}

private:
	AVLNode<T>* m_node;
};


}
