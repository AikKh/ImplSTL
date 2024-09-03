#include "avl_tree.hpp"

void AvlTest()
{
	atl::AVLTree<int> tree;

	for (int i = 0; i < 10; i++)
	{
		tree.Insert(i);
	}

	tree.Print();

	tree.Remove(3);

	tree.Print();
}