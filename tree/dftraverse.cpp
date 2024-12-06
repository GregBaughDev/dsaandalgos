#include "../test/test.h"
#include "./treenode.h"
#include "../header/queue.h"
#include <iostream>
/*
    Depth First Search (DFS)
    Description: DFS is an algorithm for traversing or searching tree or graph data structures. It explores as far down a branch as possible before backtracking.
    Implementation Hint: Use a stack (or recursion) to keep track of nodes to explore.
*/
template <typename T>
void printNode(const TreeNode<T> *node, std::string funName)
{
    std::cout << "[" << funName << "]" << " " << node->element << ", ";
}

template <typename T>
void dfPre(const TreeNode<T> *node, Queue<T> &queue)
{
    if (node == nullptr)
    {
        return;
    }
    printNode(node, "dfPre");
    queue.enqueue(node->element);
    printNode(node, "VISITNG **dfPre**");
    dfPre(node->leftNode, queue);
    dfPre(node->rightNode, queue);
}

template <typename T>
void dfIn(const TreeNode<T> *node, Queue<T> &queue)
{
    if (node == nullptr)
    {
        return;
    }
    printNode(node, "dfIn");
    dfIn(node->leftNode, queue);
    queue.enqueue(node->element);
    printNode(node, "VISITNG**dfIn**");
    dfIn(node->rightNode, queue);
}

template <typename T>
void dfPost(const TreeNode<T> *node, Queue<T> &queue)
{
    if (node == nullptr)
    {
        return;
    }
    printNode(node, "dfPost");
    dfPost(node->leftNode, queue);
    dfPost(node->rightNode, queue);
    queue.enqueue(node->element);
    printNode(node, "VISITNG**dfPost**");
}

TEST_CASE("Testing DFS - pre order")
{
    Queue<int> queue;
    TreeNode<int> rootNode{45};
    TreeNode<int> node1{98};
    TreeNode<int> node2{1};
    TreeNode<int> node3{360};
    TreeNode<int> node4{365};
    TreeNode<int> node5{69};
    TreeNode<int> node6{420};
    TreeNode<int> node7{996};
    TreeNode<int> node8{1000};
    TreeNode<int> node9{2};
    TreeNode<int> node10{54};

    rootNode.leftNode = &node1;
    rootNode.rightNode = &node2;

    node1.leftNode = &node3;
    node1.rightNode = &node4;

    node2.leftNode = &node5;
    node2.rightNode = &node6;

    node3.leftNode = &node7;
    node3.rightNode = &node8;

    node4.leftNode = &node9;
    node4.rightNode = &node10;

    dfPre(&rootNode, queue);
    std::cout << std::endl;
    /*
                   45
              /        \
              98         1
            /    \      / \
          360    365   69 420
        /    \    | \
        996 1000  2  54
    */

    CHECK(queue.dequeue() == 45);
    CHECK(queue.dequeue() == 98);
    CHECK(queue.dequeue() == 360);
    CHECK(queue.dequeue() == 996);
    CHECK(queue.dequeue() == 1000);
    CHECK(queue.dequeue() == 365);
    CHECK(queue.dequeue() == 2);
    CHECK(queue.dequeue() == 54);
    CHECK(queue.dequeue() == 1);
    CHECK(queue.dequeue() == 69);
    CHECK(queue.dequeue() == 420);
}

TEST_CASE("Testing DFS - in order")
{
    Queue<int> queue;
    TreeNode<int> rootNode{45};
    TreeNode<int> node1{98};
    TreeNode<int> node2{1};
    TreeNode<int> node3{360};
    TreeNode<int> node4{365};
    TreeNode<int> node5{69};
    TreeNode<int> node6{420};
    TreeNode<int> node7{996};
    TreeNode<int> node8{1000};
    TreeNode<int> node9{2};
    TreeNode<int> node10{54};

    rootNode.leftNode = &node1;
    rootNode.rightNode = &node2;

    node1.leftNode = &node3;
    node1.rightNode = &node4;

    node2.leftNode = &node5;
    node2.rightNode = &node6;

    node3.leftNode = &node7;
    node3.rightNode = &node8;

    node4.leftNode = &node9;
    node4.rightNode = &node10;

    dfIn(&rootNode, queue);
    std::cout << std::endl;
    /*
                   45
              /        \
              98         1
            /    \      / \
          360    365   69 420
        /    \    | \
        996 1000  2  54
    */

    CHECK(queue.dequeue() == 996);
    CHECK(queue.dequeue() == 360);
    CHECK(queue.dequeue() == 1000);
    CHECK(queue.dequeue() == 98);
    CHECK(queue.dequeue() == 2);
    CHECK(queue.dequeue() == 365);
    CHECK(queue.dequeue() == 54);
    CHECK(queue.dequeue() == 45);
    CHECK(queue.dequeue() == 69);
    CHECK(queue.dequeue() == 1);
    CHECK(queue.dequeue() == 420);
}

TEST_CASE("Testing DFS - post order")
{
    Queue<int> queue;
    TreeNode<int> rootNode{45};
    TreeNode<int> node1{98};
    TreeNode<int> node2{1};
    TreeNode<int> node3{360};
    TreeNode<int> node4{365};
    TreeNode<int> node5{69};
    TreeNode<int> node6{420};
    TreeNode<int> node7{996};
    TreeNode<int> node8{1000};
    TreeNode<int> node9{2};
    TreeNode<int> node10{54};

    rootNode.leftNode = &node1;
    rootNode.rightNode = &node2;

    node1.leftNode = &node3;
    node1.rightNode = &node4;

    node2.leftNode = &node5;
    node2.rightNode = &node6;

    node3.leftNode = &node7;
    node3.rightNode = &node8;

    node4.leftNode = &node9;
    node4.rightNode = &node10;

    dfPost(&rootNode, queue);
    std::cout << std::endl;
    /*
                   45
              /        \
              98         1
            /    \      / \
          360    365   69 420
        /    \    | \
        996 1000  2  54
    */

    CHECK(queue.dequeue() == 996);
    CHECK(queue.dequeue() == 1000);
    CHECK(queue.dequeue() == 360);
    CHECK(queue.dequeue() == 2);
    CHECK(queue.dequeue() == 54);
    CHECK(queue.dequeue() == 365);
    CHECK(queue.dequeue() == 98);
    CHECK(queue.dequeue() == 69);
    CHECK(queue.dequeue() == 420);
    CHECK(queue.dequeue() == 1);
    CHECK(queue.dequeue() == 45);
}
