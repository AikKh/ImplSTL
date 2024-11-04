#pragma once

#include "../order.hpp"

namespace atl
{

	template<typename T>
	class Inorder : public Order<T> {
	public:
		using node = AVLNode<T>*;

		Inorder(node root)
		{
			PushLeft(root);
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
				PushLeft(current->Right);
			}
		}
	
	private:
		void PushLeft(node node)
		{
			while (node != nullptr)
			{
				m_stack.push(node);
				node = node->Left;
			}
		}
	private:
		std::stack<node> m_stack;
	};

}
