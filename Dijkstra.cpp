#include "./test/test.h"
#include <vector>
#include <array>
#include <algorithm>
/*
    Dijkstra's Algorithm
    Description: Dijkstra's algorithm is used to find the shortest path from a source node to all other nodes in a weighted graph.
    Implementation Hint: Use a priority queue to efficiently get the next node with the smallest tentative distance.
*/
double inf = std::numeric_limits<double>::infinity();

struct GraphNode {
    u_int weight;
    int value;
};

template <u_long arraySize>
bool hasUnvisitedNodes(std::array<bool, arraySize> &visitedList)
{
    return std::any_of(
        visitedList.begin(),
        visitedList.end(),
        [] (const bool &b) { 
            return b == false; 
        }
    );
}

template <u_long arraySize>
int getLowestUnvisitedNode(std::array<double, arraySize> &distances, std::array<bool, arraySize> &visitedList)
{
    int idx;
    double dist = inf;

    for (int i = 0; i < distances.size(); i++)
    {
        if (!visitedList[i] && dist > distances[i])
        {
            dist = distances[i];
            idx = i;
        }
    }

    return idx;
}

template <u_long arraySize>
std::vector<int> dijkstraAdjList(std::array<std::vector<GraphNode>, arraySize> &graph, int source, int needle)
{
    std::array<double, arraySize> distances;
    std::array<bool, arraySize> visited;
    std::array<int, arraySize> prev;

    distances.fill(inf);
    visited.fill(false);

    distances[source] = 0;

    while (hasUnvisitedNodes(visited))
    {
        int currNode = getLowestUnvisitedNode(distances, visited);
        visited[currNode] = true;

        for (int i = 0; i < graph[currNode].size(); i++)
        {
            GraphNode currGraphNode = graph[currNode][i];

            if (visited[currGraphNode.value])
            {
                continue;
            }

            double distance = distances[currNode] + currGraphNode.weight;

            if (distance < distances[currGraphNode.value])
            {
                distances[currGraphNode.value] = distance;
                prev[currGraphNode.value] = currNode;
            }
        }
    }

    std::vector<int> outVec = {needle};
    int prevIndex = prev[needle];

    while (prevIndex != source)
    {
        outVec.push_back(prevIndex);
        prevIndex = prev[prevIndex];
    }

    outVec.push_back(source);

    return outVec;
}

TEST_CASE("Djikstra - Test 1")
{
    std::array<std::vector<GraphNode>, 8> graph = {
        {
            {{6, 1}, {20, 4}}, 
            {{6, 0}, {3, 4}, {10, 3}}, 
            {{4, 5}, {12, 4}, {33, 6}, {6, 7}}, 
            {{10, 1}, {9, 5}}, 
            {{20, 0}, {3, 1}, {7, 5}, {12, 2}}, 
            {{9, 3}, {7, 4}, {4, 2}}, 
            {{33, 2}},
            {{6, 2}}
        }
    };

    std::vector<int> test1 = dijkstraAdjList(graph, 7, 0);

    CHECK(test1.size() == 6);
    CHECK(test1.at(0) == 0);
    CHECK(test1.at(1) == 1);
    CHECK(test1.at(2) == 4);
    CHECK(test1.at(3) == 5);
    CHECK(test1.at(4) == 2);
    CHECK(test1.at(5) == 7);

    std::vector<int> test2 = dijkstraAdjList(graph, 6, 4);

    CHECK(test2.size() == 4);
    CHECK(test2.at(0) == 4);
    CHECK(test2.at(1) == 5);
    CHECK(test2.at(2) == 2);
    CHECK(test2.at(3) == 6);

    std::vector<int> test3 = dijkstraAdjList(graph, 1, 5);

    CHECK(test3.size() == 3);
    CHECK(test3.at(0) == 5);
    CHECK(test3.at(1) == 4);
    CHECK(test3.at(2) == 1);

    std::vector<int> test4 = dijkstraAdjList(graph, 0, 6);

    CHECK(test4.size() == 6);
    CHECK(test4.at(0) == 6);
    CHECK(test4.at(1) == 2);
    CHECK(test4.at(2) == 5);
    CHECK(test4.at(3) == 4);
    CHECK(test4.at(4) == 1);
    CHECK(test4.at(5) == 0);
}

TEST_CASE("Djikstra - Test 2")
{
    // to do
}

TEST_CASE("hasUnvisitedNodes")
{
    std::array<bool, 5> testList1 = { false, false, false, true, false };
    CHECK(hasUnvisitedNodes(testList1) == true);

    std::array<bool, 5> testList2 = { false, false, false, false, false };
    CHECK(hasUnvisitedNodes(testList2) == true);

    std::array<bool, 5> testList3 = { true, true, false, true, false };
    CHECK(hasUnvisitedNodes(testList3) == true);

    std::array<bool, 5> testList4 = { true, true, true, true, true };
    CHECK(hasUnvisitedNodes(testList4) == false);
}

TEST_CASE("getClosestUnvisitedNode")
{
    std::array<bool, 5> unvisitedList = { false, false, false, false, false };

    std::array<double, 5> testDist1 = { inf, inf, 0, 10, 9 };
    CHECK(getLowestUnvisitedNode(testDist1, unvisitedList) == 2);

    std::array<double, 5> testDist2 = { 10, 20, 100, 6, 120 };
    std::array<bool, 5> unvisitedList2 = { true, true, false, true, true };
    CHECK(getLowestUnvisitedNode(testDist2, unvisitedList) == 3);
    CHECK(getLowestUnvisitedNode(testDist2, unvisitedList2) == 2);

    std::array<double, 5> testDist3 = { 0, inf, inf, inf, inf };
    CHECK(getLowestUnvisitedNode(testDist3, unvisitedList) == 0);
}

