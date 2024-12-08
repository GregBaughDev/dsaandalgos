#include "../test/test.h"
#include "./treenode.h"
#include "../header/queue.h"
#include <iostream>

template <typename T>
void bfTraverse(TreeNode<T> *rootNode, Queue<T> &queue)
{
    if (!rootNode)
    {
        return;
    }

    Queue<TreeNode<T> *> internalQueue;
    internalQueue.enqueue(rootNode);

    std::optional<TreeNode<T> *> currNode;

    while (!internalQueue.isEmpty())
    {
        currNode = internalQueue.dequeue();

        queue.enqueue(currNode.value()->element);

        if (currNode.value()->leftNode)
        {
            internalQueue.enqueue(currNode.value()->leftNode);
        }

        if (currNode.value()->rightNode)
        {
            internalQueue.enqueue(currNode.value()->rightNode);
        }
    }
}

TEST_CASE("Testing BF traverse")
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

    bfTraverse(&rootNode, queue);

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
    CHECK(queue.dequeue() == 1);
    CHECK(queue.dequeue() == 360);
    CHECK(queue.dequeue() == 365);
    CHECK(queue.dequeue() == 69);
    CHECK(queue.dequeue() == 420);
    CHECK(queue.dequeue() == 996);
    CHECK(queue.dequeue() == 1000);
    CHECK(queue.dequeue() == 2);
    CHECK(queue.dequeue() == 54);
}
