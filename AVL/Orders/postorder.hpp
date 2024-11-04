#pragma once

#include "../order.hpp"

namespace atl
{

	template<typename T>
	class Postorder : public Order<T> {
	public:
		using node = AVLNode<T>*;

		Postorder(node root)
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
			node n = m_stack.top();
			m_stack.pop();

			if (!m_stack.empty() && n == m_stack.top()->Left)
			{
				PushLeft(m_stack.top()->Right);
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
