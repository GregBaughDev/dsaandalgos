#include "../test/test.h"
#include "./treenode.h"
#include "../header/queue.h"
/*
    Breadth First Search (BFS)
    Description: BFS is an algorithm for traversing or searching tree or graph data structures. It explores all neighbors at the present depth prior to moving on to nodes at the next depth level.
    Implementation Hint: Use a queue to keep track of nodes to explore, starting with the root or source node.
*/
template <typename T>
bool bfs(TreeNode<T> *node, T &&targetValue)
{
    if (!node)
    {
        return false;
    }

    Queue<TreeNode<T> *> internalQueue;
    internalQueue.enqueue(node);

    std::optional<TreeNode<T> *> currNode;

    while (!internalQueue.isEmpty())
    {
        currNode = internalQueue.dequeue();

        if (currNode.value()->element == targetValue)
        {
            return true;
        }

        if (currNode.value()->leftNode)
        {
            internalQueue.enqueue(currNode.value()->leftNode);
        }

        if (currNode.value()->rightNode)
        {
            internalQueue.enqueue(currNode.value()->rightNode);
        }
    }

    return false;
}

TEST_CASE("BFS testing")
{
    TreeNode<int> rootNode{146};
    TreeNode<int> node1{75};
    TreeNode<int> node2{90};
    TreeNode<int> node3{6};
    TreeNode<int> node4{1006};
    TreeNode<int> node5{851};
    TreeNode<int> node6{9};
    TreeNode<int> node7{8883};
    TreeNode<int> node8{92};
    TreeNode<int> node9{37};
    TreeNode<int> node10{40};
    TreeNode<int> node11{11};
    TreeNode<int> node12{360};
    TreeNode<int> node13{365};

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

    node5.leftNode = &node11;
    node5.rightNode = &node12;

    node6.leftNode = &node13;

    CHECK(bfs(&rootNode, 146) == true);
    CHECK(bfs(&rootNode, 9) == true);
    CHECK(bfs(&rootNode, 360) == true);
    CHECK(bfs(&rootNode, 365) == true);
    CHECK(bfs(&rootNode, 11) == true);
    CHECK(bfs(&rootNode, 37) == true);
    CHECK(bfs(&rootNode, 8883) == true);
    CHECK(bfs(&rootNode, 40) == true);
    CHECK(bfs(&rootNode, 851) == true);
    CHECK(bfs(&rootNode, 6) == true);
    CHECK(bfs(&rootNode, 92) == true);
    CHECK(bfs(&rootNode, 75) == true);
    CHECK(bfs(&rootNode, 90) == true);
    CHECK(bfs(&rootNode, 1006) == true);

    CHECK(bfs(&rootNode, 69) == false);
    CHECK(bfs(&rootNode, 420) == false);
    CHECK(bfs(&rootNode, 123) == false);
    CHECK(bfs(&rootNode, 10092) == false);
    CHECK(bfs(&rootNode, 10) == false);
    CHECK(bfs(&rootNode, 66) == false);
    CHECK(bfs(&rootNode, 99) == false);
}
