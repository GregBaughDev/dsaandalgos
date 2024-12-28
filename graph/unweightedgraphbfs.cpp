#include "../test/test.h"
#include "../header/queue.h"
#include <vector>
#include <array>
/*
    Unweighted Graph
    Description: An unweighted graph is a graph where all edges have the same weight, typically treated as having a weight of one.
    Implementation Hint: Represent it using an adjacency list or matrix without concern for edge weights.
*/
template <u_long arraySize>
std::vector<int> bfsMatrix(std::array<std::array<int, arraySize>, arraySize> &graph, int source, int needle)
{
    if (needle >= arraySize)
        // check that the needle is within the bounds of the arraysize
        return {};

    std::array<bool, arraySize> seen;
    std::array<int, arraySize> prev;
    Queue<int> queue;

    prev.fill(-1);
    seen.fill(false);

    queue.enqueue(source);
    seen[source] = true;

    while (!queue.isEmpty())
    {
        int currValue = queue.dequeue().value();

        for (int i = 0; i < graph[currValue].size(); i++)
        {
            if (seen[i] || graph[currValue][i] == 0) // we've already seen the value or no link
                continue;

            seen[i] = true;
            prev[i] = currValue;

            if (i == needle)
                break;

            queue.enqueue(i);
        }
    }

    if (prev[needle] == -1)
        return {};

    std::vector<int> outVec = {needle};

    int traceBack = prev[needle];
    while (traceBack != -1)
    {
        outVec.push_back(traceBack);
        traceBack = prev[traceBack];
    }

    return outVec;
}

TEST_CASE("Unweighted graph - BFS - adjacency matrix test 1")
{
    std::array<std::array<int, 9>, 9> graph = {
        {
          // 0, 1, 2, 3, 4, 5, 6, 7, 8
            {0, 1, 0, 1, 0, 1, 1, 1, 1}, // 0
            {1, 0, 0, 0, 0, 1, 0, 0, 1}, // 1
            {0, 0, 0, 0, 0, 1, 0, 0, 0}, // 2
            {1, 0, 0, 0, 0, 0, 0, 0, 0}, // 3
            {0, 0, 0, 0, 0, 1, 0, 0, 0}, // 4
            {1, 1, 1, 0, 1, 0, 0, 0, 1}, // 5
            {1, 0, 0, 0, 0, 0, 0, 0, 0}, // 6
            {1, 0, 0, 0, 0, 0, 0, 0, 1}, // 7
            {1, 1, 0, 0, 0, 0, 0, 1, 0}, // 8
        }};

    std::vector<int> traversal1 = bfsMatrix(graph, 1, 4);

    CHECK(traversal1.size() == 3);
    CHECK(traversal1.at(0) == 4);
    CHECK(traversal1.at(1) == 5);
    CHECK(traversal1.at(2) == 1);

    std::vector<int> traversal2 = bfsMatrix(graph, 7, 2);

    CHECK(traversal2.size() == 4);
    CHECK(traversal2.at(0) == 2);
    CHECK(traversal2.at(1) == 5);
    CHECK(traversal2.at(2) == 0);
    CHECK(traversal2.at(3) == 7);
    
    std::vector<int> traversal3 = bfsMatrix(graph, 8, 1);

    CHECK(traversal3.size() == 2);
    CHECK(traversal3.at(0) == 1);
    CHECK(traversal3.at(1) == 8);

    std::vector<int> traversal4 = bfsMatrix(graph, 0, 10);
    CHECK(traversal4.size() == 0);
}

TEST_CASE("Unweighted graph - BFS - adjacency matrix test 1")
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

    std::vector<int> traversal1 = bfsMatrix(graph, 1, 4);

    CHECK(traversal1.size() == 5);
    CHECK(traversal1.at(0) == 4);
    CHECK(traversal1.at(1) == 6);
    CHECK(traversal1.at(2) == 8);
    CHECK(traversal1.at(3) == 0);
    CHECK(traversal1.at(4) == 1);

    std::vector<int> traversal2 = bfsMatrix(graph, 7, 15);

    CHECK(traversal2.size() == 9);
    CHECK(traversal2.at(0) == 15);
    CHECK(traversal2.at(1) == 3);
    CHECK(traversal2.at(2) == 13);
    CHECK(traversal2.at(3) == 6);
    CHECK(traversal2.at(4) == 8);
    CHECK(traversal2.at(5) == 0);
    CHECK(traversal2.at(6) == 1);
    CHECK(traversal2.at(7) == 9);
    CHECK(traversal2.at(8) == 7);

    std::vector<int> traversal3 = bfsMatrix(graph, 0, 10);

    CHECK(traversal3.size() == 5);
    CHECK(traversal3.at(0) == 10);
    CHECK(traversal3.at(1) == 13);
    CHECK(traversal3.at(2) == 6);
    CHECK(traversal3.at(3) == 8);
    CHECK(traversal3.at(4) == 0);

    std::vector<int> traversal4 = bfsMatrix(graph, 4, 15);

    CHECK(traversal4.size() == 5);
    CHECK(traversal4.at(0) == 15);
    CHECK(traversal4.at(1) == 3);
    CHECK(traversal4.at(2) == 13);
    CHECK(traversal4.at(3) == 6);
    CHECK(traversal4.at(4) == 4);
}

// adjacency list
