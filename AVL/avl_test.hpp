#include "avl_tree.hpp"

void AvlTest()
{
	atl::AVLTree<int> tree;

	for (int i = 1; i < 3; i++)
	{
		tree.Insert(i);
	}

	tree.Print();

	/*std::cout << "Inorder: ";
	for (auto& node : tree.Inorder())
	{
		std::cout << node.Value << ", ";
	}
	std::cout << std::endl;


	std::cout << "Preorder: ";
	for (auto& node : tree.Preorder())
	{
		std::cout << node.Value << ", ";
	}
	std::cout << std::endl;*/

	std::cout << "Postorder: ";
	for (auto& node : tree.Postorder())
	{
		std::cout << node.Value << ", ";
	}
	std::cout << std::endl;


}