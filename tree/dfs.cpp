#include "../test/test.h"
#include "./treenode.h"
#include "../header/queue.h"
/*
    Depth First Search (DFS)
    Description: DFS is an algorithm for traversing or searching tree or graph data structures. It explores as far down a branch as possible before backtracking.
    Implementation Hint: Use a stack (or recursion) to keep track of nodes to explore.
*/
template <typename T>
void dfsRecurse(TreeNode<T> *node, T targetValue, bool *result)
{
    if (node == nullptr)
    {
        return;
    }

    if (node->element == targetValue)
    {
        *result = true;
    }

    dfsRecurse(node->leftNode, targetValue, result);
    dfsRecurse(node->rightNode, targetValue, result);
}

template <typename T>
bool dfs(TreeNode<T> *node, T targetValue) // returning a result from a recursive function is tricky
{   
    bool result = false;
    dfsRecurse(node, targetValue, &result);
    return result;
}


TEST_CASE("DFS testing")
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

    CHECK(dfs(&rootNode, 146) == true);
    CHECK(dfs(&rootNode, 9) == true);
    CHECK(dfs(&rootNode, 360) == true);
    CHECK(dfs(&rootNode, 365) == true);
    CHECK(dfs(&rootNode, 11) == true);
    CHECK(dfs(&rootNode, 37) == true);
    CHECK(dfs(&rootNode, 8883) == true);
    CHECK(dfs(&rootNode, 40) == true);
    CHECK(dfs(&rootNode, 851) == true);
    CHECK(dfs(&rootNode, 6) == true);
    CHECK(dfs(&rootNode, 92) == true);
    CHECK(dfs(&rootNode, 75) == true);
    CHECK(dfs(&rootNode, 90) == true);
    CHECK(dfs(&rootNode, 1006) == true);

    CHECK(dfs(&rootNode, 69) == false);
    CHECK(dfs(&rootNode, 420) == false);
    CHECK(dfs(&rootNode, 123) == false);
    CHECK(dfs(&rootNode, 10092) == false);
    CHECK(dfs(&rootNode, 10) == false);
    CHECK(dfs(&rootNode, 66) == false);
    CHECK(dfs(&rootNode, 99) == false);
}

