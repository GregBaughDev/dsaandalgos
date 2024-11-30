#include "./test/test.h"
#include "./complete/mergesort.cpp"
#include <iostream>
/*
    Binary Search
    Description: Binary search is an efficient algorithm for finding an item from a sorted list of items. It works by repeatedly dividing the search interval in half.
    Implementation Hint: Ensure the input array is sorted and use a loop or recursion to divide the search space.
*/
class BinarySearch
{
public:
    static int search(const std::vector<int>& list, int item);

private:
    static int searchInList(const std::vector<int>& list, int item, int startIdx, int endIdx);
};

int BinarySearch::search(const std::vector<int>& list, int item)
{
    return searchInList(list, item, 0, list.size() - 1);
}

int BinarySearch::searchInList(const std::vector<int>& list, int item, int startIdx, int endIdx)
{
    if (startIdx == endIdx) return -1;

    int midPoint = (endIdx - startIdx) / 2 + startIdx;

    if (
        list[midPoint] == item || 
        list[startIdx] == item || 
        list[endIdx] == item
        )
    {
        return item;
    } 

    if (list[midPoint] > item) {
        return searchInList(list, item, startIdx, midPoint - 1);
    }

    if (list[midPoint] < item) {
        return searchInList(list, item, midPoint + 1, endIdx);
    }

    return -1;
}

TEST_CASE("testing BinarySearch - 1")
{
    MergeSort mergesort{{36, 123, 489, 3548, 7, 93, 69, 3734, 12394, 774, 28384, 489392, 12398, 9823, 182374, 182837}};
    CHECK(BinarySearch::search(mergesort.getList(), 774) == 774);
    CHECK(BinarySearch::search(mergesort.getList(), 69) == 69);
    CHECK(BinarySearch::search(mergesort.getList(), 3) == -1);
    CHECK(BinarySearch::search(mergesort.getList(), 12394) == 12394);
    CHECK(BinarySearch::search(mergesort.getList(), 489392) == 489392);
    CHECK(BinarySearch::search(mergesort.getList(), 489) == 489);
    CHECK(BinarySearch::search(mergesort.getList(), 36) == 36);
    CHECK(BinarySearch::search(mergesort.getList(), 100000000) == -1);
}