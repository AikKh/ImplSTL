#include <iostream>
#include <queue>
#include <algorithm>
#include "avl_node.hpp"

namespace atl
{

template<Comparable T>
class AVLTree {
public:
	using Node = AVLNode<T>;

	void Insert(int value)
	{
		m_root = InsertHelper(m_root, value);
	}

	void Remove(int value)
	{
		m_root = RemoveHelper(m_root, value);
	}

	void Print() const
	{
		PrintBT("", m_root, false);
	}

	~AVLTree()
	{
		Delete(m_root);
	}

private:
	Node* InsertHelper(Node* node, int value)
	{
		if (node == nullptr)
		{
			return new Node{ value };
		}

		if (node->Value > value)
			node->Left = InsertHelper(node->Left, value);
		else if (node->Value < value)
			node->Right = InsertHelper(node->Right, value);
		else
			return node;

		UpdateHeight(node);
		
		return Balance(node);
	}

	Node* RemoveHelper(Node* node, int value)
	{
		if (node == nullptr)
		{
			return node; // Node does not exist
		}

		if (node->Value > value)
		{
			node->Left = RemoveHelper(node->Left, value);
		}
		else if (node->Value < value)
		{
			node->Right = RemoveHelper(node->Right, value);
		}
		else
		{
			if (!node->Left && !node->Right)
			{
				delete node;
				return nullptr;
			}
			else if (node->Left && !node->Right)
			{
				auto left = node->Left;
				delete node;
				return left;
			}
			else if (!node->Left && node->Right)
			{
				auto right = node->Right;
				delete node;
				return right;
			}
			else
			{
				Node* successor;
				if (node->Left->Height > node->Right->Height)
				{
					successor = node->Left->GetRightSuccessor();
					node->Value = successor->Value;
					node->Left = RemoveHelper(node->Left, successor->Value);
				}
				else
				{
					successor = node->Right->GetLeftSuccessor();
					node->Value = successor->Value;
					node->Right = RemoveHelper(node->Right, successor->Value);
				}
			}
			
		}

		UpdateHeight(node);
		return Balance(node);
	}

	int UpdateHeight(Node* node)
	{
		if (!node)
			return -1;

		auto l = UpdateHeight(node->Left);
		auto r = UpdateHeight(node->Right);

		node->Height = 1 + std::max(l, r);
		node->Factor = r - l;

		return node->Height;
	}

	Node* Balance(Node* node)
	{
		if (-2 < node->Factor && node->Factor < 2)
			return node;

		std::cout << "Balance\n";
		if (node->Factor < 0 && node->Left->Factor < 0)
		{
			return RightRotation(node);
		}
		else if (node->Factor < 0 && node->Left->Factor > 0)
		{
			return LeftRightRotation(node);
		}
		else if (node->Factor > 0 && node->Right->Factor > 0)
		{
			return LeftRotation(node);
		}
		else if (node->Factor > 0 && node->Right->Factor < 0)
		{
			return RightLeftRotation(node);
		}

		throw std::logic_error("Something went wrong");
	}

	Node* RightRotation(Node* node)
	{
		auto left = node->Left;
		node->Left = left->Right;
		left->Right = node;

		UpdateHeight(left);
		return left;
	}

	Node* LeftRotation(Node* node)
	{
		auto right = node->Right;
		node->Right = right->Left;
		right->Left = node;

		UpdateHeight(right);
		return right;
	}

	Node* LeftRightRotation(Node* node)
	{
		node->Left = LeftRotation(node->Left);
		return RightRotation(node);
	}

	Node* RightLeftRotation(Node* node)
	{
		node->Right = RightRotation(node->Right);
		return LeftRotation(node);
	}

	void Delete(Node* node)
	{
		if (node->Left)
		{
			Delete(node->Left);
		}
		if (node->Right)
		{
			Delete(node->Right);
		}
		delete node;
	}

	static void PrintBT(const std::string& prefix, const Node* node, bool isLeft)
	{
		if (node != nullptr)
		{
			std::cout << prefix;
			std::cout << (isLeft?"+--":"\\--");
			std::cout << node->Value << std::endl;
			PrintBT(prefix + (isLeft?"|   ":"    "), node->Left, true);
			PrintBT(prefix + (isLeft?"|   ":"    "), node->Right, false);
		}
	}

private:
//public:
	Node* m_root = nullptr;
};

}