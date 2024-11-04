#pragma once

#include "../order.hpp"

namespace atl
{

	template<typename T>
	class Preorder : public Order<T> {
	public:
		using node = AVLNode<T>*;

		Preorder(node root)
		{
			m_stack.push(root);
		}

		virtual node GetCurrent() const override
		{
			if (m_stack.empty())
				return nullptr;

			return m_stack.top();
		}

		virtual void Next() override
		{
			if (m_stack.empty())
				return;

			node current = m_stack.top();
			m_stack.pop();

			if (current->Right != nullptr)
			{
				m_stack.push(current->Right);
			}
			if (current->Left != nullptr)
			{
				m_stack.push(current->Left);
			}
		}

	private:
		std::stack<node> m_stack;
	};

}
