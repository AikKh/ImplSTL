#include <concepts>

namespace atl
{

template <typename T>
concept Comparable = requires(T a, T b)
{
    { a == b } -> std::same_as<bool>;
    { a > b } -> std::same_as<bool>;
    { a < b } -> std::same_as<bool>;
};

template<Comparable T>
class AVLNode {
public:
    AVLNode(int value, AVLNode* left = nullptr, AVLNode* right = nullptr) : Value{ value }, Left{ left }, Right{ right } {}

    AVLNode* GetLeftSuccessor()
    {
        return GetSuccessor<&AVLNode::Left>(this);
    }

    AVLNode* GetRightSuccessor()
    {
        return GetSuccessor<&AVLNode::Right>(this);
    }

	int Height = 1;
	int Factor = 0;
    T Value;
	AVLNode* Left;
    AVLNode* Right;

private:
    using NodePtr = AVLNode * AVLNode::*;

    template <NodePtr dir>
    static AVLNode* GetSuccessor(AVLNode* node)
    {
        if (node->*dir)
            return GetSuccessor<dir>(node->*dir);
        return node;
    }
};

}