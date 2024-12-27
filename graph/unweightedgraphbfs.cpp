#include "../test/test.h"
#include <vector>
#include <array>
#include <iostream>
#include "../header/queue.h"
/*
    Unweighted Graph
    Description: An unweighted graph is a graph where all edges have the same weight, typically treated as having a weight of one.
    Implementation Hint: Represent it using an adjacency list or matrix without concern for edge weights.
*/
// adjacency matrix -- WIP!
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

    std::vector<int> outVec = {needle}; // UP TO HERE - reverse the outvec

    int traceBack = prev[needle];
    while (traceBack != -1)
    {
        outVec.push_back(traceBack);
        traceBack = prev[traceBack];
    }

    for (auto c : outVec)
        std::cout << "C -> " << c << "\n";

    return outVec;
}

TEST_CASE("Unweighted graph - BFS - adjacency matrix")
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
    bfsMatrix(graph, 1, 4);
}

// test a bigger graph
// test values not in the graph
// test needle bigger than size

// adjacency list
