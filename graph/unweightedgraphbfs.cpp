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
template<ulong arraySize>
std::vector<int> bfsMatrix(std::array<std::array<int, arraySize>, arraySize> &graph, int source, int needle)
{
    if (needle >= arraySize)
    // check that the needle is within the bounds of the arraysize
        return {};

    std::array<bool, arraySize> seen;
    std::array<int, arraySize> prev;
    Queue<int> queue;

    prev.fill(-1);

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

            if (graph[currValue][i] == needle)
                break;

            prev[i] = currValue;
            queue.enqueue(i);
        }
    }

    if (prev[needle] == -1)
        return {};
    
    std::vector<int> outVec = { needle }; // UP TO HERE - reverse the outvec

    int traceBack = prev[needle];
    while (traceBack != -1)
    {
        outVec.push_back(traceBack);
        traceBack = prev[traceBack];
    }

    return outVec;
}

TEST_CASE("Unweighted graph - BFS - adjacency matrix")
{
    std::array<std::array<int, 9>, 9> graph = {
        {
            {0, 1, 0, 1, 0, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 1, 0, 0, 1},
            {0, 0, 0, 0, 0, 1, 0, 0, 0},
            {1, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 0, 0, 0},
            {1, 1, 1, 0, 1, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 0, 0, 0, 0, 0, 1, 0},
        }
    };
    bfsMatrix(graph, 1, 4);
}

// adjacency list