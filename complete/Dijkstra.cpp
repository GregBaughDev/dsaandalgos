#include "../test/test.h"
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

TEST_CASE("Dijkstra - Test 1")
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

TEST_CASE("Dijkstra - Test 2")
{
    std::array<std::vector<GraphNode>, 21> graph = {
        {
            {{1, 9}},
            {{9, 5}, {8, 4}, {5, 6}},
            {{4, 11}, {5, 19}},
            {{7, 6}, {2, 4}, {9, 17}},
            {{1, 5}, {8, 1}, {2, 3}, {10, 15}},
            {{13, 20}, {1, 4}, {9, 1}},
            {{5, 1}, {7, 3}},
            {{8, 9}, {7, 8}, {1, 20}, {6, 10}},
            {{7, 7}},
            {{1, 0}, {8, 7}},
            {{6, 7}, {3, 12}},
            {{6, 14}, {4, 2}, {19, 13}},
            {{3, 10}, {1, 19}},
            {{19, 11}},
            {{2, 20}, {6, 11}},
            {{10, 4}, {11, 16}},
            {{11, 15}, {4, 17}, {2, 18}},
            {{9, 3}, {4, 16}, {3, 19}},
            {{6, 20}, {2, 16}},
            {{3, 17}, {5, 2}, {1, 12}},
            {{1, 7}, {2, 14}, {13, 5}, {6, 18}}
        }
    };

    std::vector<int> test1 = dijkstraAdjList(graph, 0, 19);

    CHECK(test1.size() == 6);
    CHECK(test1.at(0) == 19);
    CHECK(test1.at(1) == 12);
    CHECK(test1.at(2) == 10);
    CHECK(test1.at(3) == 7);
    CHECK(test1.at(4) == 9);
    CHECK(test1.at(5) == 0);

    std::vector<int> test2 = dijkstraAdjList(graph, 11, 1);

    CHECK(test2.size() == 5);
    CHECK(test2.at(0) == 1);
    CHECK(test2.at(1) == 5);
    CHECK(test2.at(2) == 20);
    CHECK(test2.at(3) == 14);
    CHECK(test2.at(4) == 11);

    std::vector<int> test3 = dijkstraAdjList(graph, 13, 18);

    CHECK(test3.size() == 5);
    CHECK(test3.at(0) == 18);
    CHECK(test3.at(1) == 20);
    CHECK(test3.at(2) == 14);
    CHECK(test3.at(3) == 11);
    CHECK(test3.at(4) == 13);

    std::vector<int> test4 = dijkstraAdjList(graph, 10, 15);

    CHECK(test4.size() == 6);
    CHECK(test4.at(0) == 15);
    CHECK(test4.at(1) == 16);
    CHECK(test4.at(2) == 17);
    CHECK(test4.at(3) == 19);
    CHECK(test4.at(4) == 12);
    CHECK(test4.at(5) == 10);

    std::vector<int> test5 = dijkstraAdjList(graph, 9, 6);

    CHECK(test5.size() == 7);
    CHECK(test5.at(0) == 6);
    CHECK(test5.at(1) == 3);
    CHECK(test5.at(2) == 4);
    CHECK(test5.at(3) == 5);
    CHECK(test5.at(4) == 20);
    CHECK(test5.at(5) == 7);
    CHECK(test5.at(6) == 9);
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

