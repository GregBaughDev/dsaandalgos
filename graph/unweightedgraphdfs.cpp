#include "../test/test.h"
#include "../header/queue.h"
#include <vector>
#include <array>
#include <iostream>
/*
    NB - DFS can return longer paths that BFS, depending on the order of nodes in the adjacency list
    Unweighted Graph
    Description: An unweighted graph is a graph where all edges have the same weight, typically treated as having a weight of one.
    Implementation Hint: Represent it using an adjacency list or matrix without concern for edge weights.
*/
// adjacency matrix
template <u_long arraySize>
bool traverseGraphMatrix(
    std::array<std::array<int, arraySize>, arraySize> &graph,
    std::vector<int> &prev,
    std::array<bool, arraySize> &seen,
    int &needle,
    int &currVal
)
{
    if (seen[currVal])
    {
        return false;
    }

    seen[currVal] = true;
    prev.push_back(currVal);

    if (currVal == needle)
    {
        return true;
    }

    for (int i = 0; i < arraySize; i++)
    {
        if (graph[currVal][i] == 1 && traverseGraphMatrix(graph, prev, seen, needle, i))
        {
            return true;
        }
    }

    prev.pop_back();
    return false;
}

template<u_long arraySize>
std::vector<int> dfsMatrix(std::array<std::array<int, arraySize>, arraySize> &graph, int source, int needle)
{
    std::array<bool, arraySize> seen;
    std::vector<int> prev;
    seen.fill(false);

    traverseGraphMatrix(graph, prev, seen, needle, source);
    return prev;
}

TEST_CASE("Unweighted graph - DFS - adjacency matrix test 1")
{
    std::array<std::array<int, 9>, 9> graph = {
        {
            // 0, 1, 2, 3, 4, 5, 6, 7, 8
            {0, 1, 0, 1, 0, 1, 1, 1, 1}, // 0
            {1, 0, 0, 0, 0, 1, 0, 0, 1}, // 1
            {0, 0, 0, 0, 0, 1, 0, 0, 0}, // 2
            {1, 0, 0, 0, 0, 0, 0, 0, 0}, // 3
            {0, 0, 0, 0, 0, 1, 0, 0, 0}, // 4
            {1, 1, 1, 0, 1, 0, 0, 0, 0}, // 5
            {1, 0, 0, 0, 0, 0, 0, 0, 0}, // 6
            {1, 0, 0, 0, 0, 0, 0, 0, 1}, // 7
            {1, 1, 0, 0, 0, 0, 0, 1, 0}, // 8
        }};

    std::vector<int> traversal1 = dfsMatrix(graph, 1, 4);

    CHECK(traversal1.size() == 4);
    CHECK(traversal1.at(0) == 1);
    CHECK(traversal1.at(1) == 0);
    CHECK(traversal1.at(2) == 5);
    CHECK(traversal1.at(3) == 4);

    std::vector<int> traversal2 = dfsMatrix(graph, 7, 2);

    CHECK(traversal2.size() == 5);
    CHECK(traversal2.at(0) == 7);
    CHECK(traversal2.at(1) == 0);
    CHECK(traversal2.at(2) == 1);
    CHECK(traversal2.at(3) == 5);
    CHECK(traversal2.at(4) == 2);

    std::vector<int> traversal3 = dfsMatrix(graph, 8, 1);

    CHECK(traversal3.size() == 3);
    CHECK(traversal3.at(0) == 8);
    CHECK(traversal3.at(1) == 0);
    CHECK(traversal3.at(2) == 1);

    std::vector<int> traversal4 = dfsMatrix(graph, 0, 10);
    CHECK(traversal4.size() == 0);
}

TEST_CASE("Unweighted graph - DFS - adjacency matrix test 2")
{
    std::array<std::array<int, 16>, 16> graph = {
        {
            // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
            {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}, // 0
            {1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0}, // 1
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 2
            {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1}, // 3
            {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 4
            {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0}, // 5
            {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0}, // 6
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0}, // 7
            {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0}, // 8
            {0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0}, // 9
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, // 10
            {0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0}, // 11
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 12
            {0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0}, // 13
            {0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, // 14
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 15
        }};

    std::vector<int> traversal1 = dfsMatrix(graph, 1, 4);

    CHECK(traversal1.size() == 5);
    CHECK(traversal1.at(0) == 1);
    CHECK(traversal1.at(1) == 0);
    CHECK(traversal1.at(2) == 8);
    CHECK(traversal1.at(3) == 6);
    CHECK(traversal1.at(4) == 4);

    std::vector<int> traversal2 = dfsMatrix(graph, 7, 15);

    CHECK(traversal2.size() == 9);
    CHECK(traversal2.at(0) == 7);
    CHECK(traversal2.at(1) == 9);
    CHECK(traversal2.at(2) == 1);
    CHECK(traversal2.at(3) == 0);
    CHECK(traversal2.at(4) == 8);
    CHECK(traversal2.at(5) == 6);
    CHECK(traversal2.at(6) == 13);
    CHECK(traversal2.at(7) == 3);
    CHECK(traversal2.at(8) == 15);

    std::vector<int> traversal3 = dfsMatrix(graph, 0, 10);

    CHECK(traversal3.size() == 8);
    CHECK(traversal3.at(0) == 0);
    CHECK(traversal3.at(1) == 1);
    CHECK(traversal3.at(2) == 5);
    CHECK(traversal3.at(3) == 14);
    CHECK(traversal3.at(4) == 8);
    CHECK(traversal3.at(5) == 6);
    CHECK(traversal3.at(6) == 13);
    CHECK(traversal3.at(7) == 10);

    std::vector<int> traversal4 = dfsMatrix(graph, 4, 15);

    CHECK(traversal4.size() == 5);
    CHECK(traversal4.at(0) == 4);
    CHECK(traversal4.at(1) == 6);
    CHECK(traversal4.at(2) == 13);
    CHECK(traversal4.at(3) == 3);
    CHECK(traversal4.at(4) == 15);
}

// adjacency list
template <u_long arraySize>
bool traverseGraphList(
    std::array<std::vector<int>, arraySize> &graph,
    std::vector<int> &prev,
    std::array<bool, arraySize> &seen,
    int &needle,
    int &currVal
)
{
    if (seen[currVal])
    {
        return false;
    }

    seen[currVal] = true;
    prev.push_back(currVal);

    if (currVal == needle)
    {
        return true;
    }

    for (int i = 0; i < graph[currVal].size(); i++)
    {
        if (traverseGraphList(graph, prev, seen, needle, graph[currVal][i]))
        {
            return true;
        }
    }

    prev.pop_back();
    return false;
}

template<u_long arraySize>
std::vector<int> dfsList(std::array<std::vector<int>, arraySize> &graph, int source, int needle)
{
    std::array<bool, arraySize> seen;
    std::vector<int> prev;
    seen.fill(false);

    traverseGraphList(graph, prev, seen, needle, source);
    return prev;
}

TEST_CASE("Unweighted graph - BFS - adjacency list test 1")
{
    std::array<std::vector<int>, 9> graph = {
        {
            {1, 3, 5, 6, 7, 8}, // 0
            {0, 5, 8},          // 1
            {5},                // 2
            {0},                // 3
            {5},                // 4
            {0, 1, 2, 4},       // 5
            {0},                // 6
            {0, 8},             // 7
            {0, 1, 7}           // 8
        }
    };

    std::vector<int> traversal1 = dfsList(graph, 1, 4);

    CHECK(traversal1.size() == 4);
    CHECK(traversal1.at(0) == 1);
    CHECK(traversal1.at(1) == 0);
    CHECK(traversal1.at(2) == 5);
    CHECK(traversal1.at(3) == 4);

    std::vector<int> traversal2 = dfsList(graph, 7, 2);

    CHECK(traversal2.size() == 5);
    CHECK(traversal2.at(0) == 7);
    CHECK(traversal2.at(1) == 0);
    CHECK(traversal2.at(2) == 1);
    CHECK(traversal2.at(3) == 5);
    CHECK(traversal2.at(4) == 2);

    std::vector<int> traversal3 = dfsList(graph, 8, 1);

    CHECK(traversal3.size() == 3);
    CHECK(traversal3.at(0) == 8);
    CHECK(traversal3.at(1) == 0);
    CHECK(traversal3.at(2) == 1);

    std::vector<int> traversal4 = dfsList(graph, 0, 10);
    CHECK(traversal4.size() == 0);
}

TEST_CASE("Unweighted graph - BFS - adjacency list test 2")
{
    std::array<std::vector<int>, 16> graph = {
        {
            {1, 8, 12}, // 0
            {0, 5, 9, 11}, // 1
            {3}, // 2
            {2, 13, 15}, // 3
            {6}, // 4
            {1, 9, 14}, // 5
            {4, 8, 13}, // 6
            {9, 11}, // 7
            {0, 6, 14}, // 8
            {1, 5, 7, 11}, // 9
            {13}, // 10
            {1, 7, 9}, // 11
            {0}, // 12
            {3, 6, 10}, // 13
            {5, 8}, // 14
            {3} // 15
        }
    };

    std::vector<int> traversal1 = dfsList(graph, 1, 4);

    CHECK(traversal1.size() == 5);
    CHECK(traversal1.at(0) == 1);
    CHECK(traversal1.at(1) == 0);
    CHECK(traversal1.at(2) == 8);
    CHECK(traversal1.at(3) == 6);
    CHECK(traversal1.at(4) == 4);

    std::vector<int> traversal2 = dfsList(graph, 7, 15);

    CHECK(traversal2.size() == 9);
    CHECK(traversal2.at(0) == 7);
    CHECK(traversal2.at(1) == 9);
    CHECK(traversal2.at(2) == 1);
    CHECK(traversal2.at(3) == 0);
    CHECK(traversal2.at(4) == 8);
    CHECK(traversal2.at(5) == 6);
    CHECK(traversal2.at(6) == 13);
    CHECK(traversal2.at(7) == 3);
    CHECK(traversal2.at(8) == 15);

    std::vector<int> traversal3 = dfsList(graph, 0, 10);

    CHECK(traversal3.size() == 8);
    CHECK(traversal3.at(0) == 0);
    CHECK(traversal3.at(1) == 1);
    CHECK(traversal3.at(2) == 5);
    CHECK(traversal3.at(3) == 14);
    CHECK(traversal3.at(4) == 8);
    CHECK(traversal3.at(5) == 6);
    CHECK(traversal3.at(6) == 13);
    CHECK(traversal3.at(7) == 10);

    std::vector<int> traversal4 = dfsList(graph, 4, 15);

    CHECK(traversal4.size() == 5);
    CHECK(traversal4.at(0) == 4);
    CHECK(traversal4.at(1) == 6);
    CHECK(traversal4.at(2) == 13);
    CHECK(traversal4.at(3) == 3);
    CHECK(traversal4.at(4) == 15);
}