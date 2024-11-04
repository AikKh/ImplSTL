#pragma once

#include <stack>
#include "avl_node.hpp"

namespace atl
{

template<typename T>
class Order {
public:
	virtual AVLNode<T>* GetCurrent() const = 0;

	virtual void Next() = 0;
};

}
