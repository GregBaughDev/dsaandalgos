#ifndef TREENODE_H
#define TREENODE_H

template <typename T>
class TreeNode
{
public:
    TreeNode(T element) : element{element} {};
    T element;
    TreeNode<T> *leftNode = nullptr;
    TreeNode<T> *rightNode = nullptr;
};

#endif
