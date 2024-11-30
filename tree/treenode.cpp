template <typename T>
class TreeNode
{
public:
    Node(T element) : element{element} {};
    T element;
    Node *leftNode = nullptr;
    Node *rightNode = nullptr;
};
