#include "../test/test.h"
#include <vector>
#include <cassert>
#include <iostream>
#include <optional>
/*
    Min Heap
    Description: A min heap is a complete binary tree where the value of each node is less than or equal to the values of its children, ensuring the minimum element is at the root.
    Implementation Hint: Similar to max heap, implement insertion and deletion while maintaining the heap property.
*/
class MinHeap
{
public:
    MinHeap() : length{0}, items{} {};
    int peek();
    void push(int value);
    int pop();
    int getLength();

private:
    int length;
    std::vector<int> items;
    int getLeftIndex(int index);
    int getRightIndex(int index);
    int getParentIndex(int index);
    void heapifyDown(int index);
    void heapifyUp(int index);
};

int MinHeap::pop()
{
    // pop is fucked
    int item = items.front();
    length--;
    items.at(0) = items.at(length);

    if (length > 0)
    {
        items.pop_back();
    }

    heapifyDown(0);
    return item;
}

void MinHeap::push(int value)
{
    items.push_back(value);
    length++;
    heapifyUp(length - 1);
}

void MinHeap::heapifyUp(int index)
{
    if (index == 0)
    {
        return;
    }

    int indexValue = items.at(index);
    int parentIndex = getParentIndex(index);
    int parentValue = items.at(parentIndex);

    if (indexValue < parentValue)
    {
        items.at(index) = parentValue;
        items.at(parentIndex) = indexValue;
        heapifyUp(parentIndex);
    }
}

void MinHeap::heapifyDown(int index)
{
    if (index > length - 1)
    {
        return;
    }

    int indexValue = items.at(index);
    int leftIndex = getLeftIndex(index);
    int rightIndex = getRightIndex(index);

    std::optional<int> leftValue = std::nullopt;
    std::optional<int> rightValue = std::nullopt;

    if (leftIndex < length) 
    {
        leftValue = items.at(leftIndex);
    }
    
    if (rightIndex < length)
    {
        rightValue = items.at(rightIndex);
    }

    if (leftValue.has_value() && rightValue.has_value())
    {
        if (leftValue < rightValue && leftValue < indexValue)
        {
            items.at(leftIndex) = indexValue;
            items.at(index) = leftValue.value();
            return heapifyDown(leftIndex);
        }
        else if (rightValue < leftValue && rightValue < indexValue)
        {
            items.at(rightIndex) = indexValue;
            items.at(index) = rightValue.value();
            return heapifyDown(rightIndex);
        }
    }

    if (rightValue.has_value() && rightValue < indexValue)
    {
        items.at(rightIndex) = indexValue;
        items.at(index) = rightValue.value();
        return heapifyDown(rightIndex);
    }

    if (leftValue.has_value() && leftValue < indexValue)
    {
        items.at(leftIndex) = indexValue;
        items.at(index) = leftValue.value();
        return heapifyDown(leftIndex);
    }
}

int MinHeap::peek()
{
    return items[0];
}

int MinHeap::getLeftIndex(int index)
{
    return (2 * index) + 1;
}

int MinHeap::getRightIndex(int index)
{
    return (2 * index) + 2;
}

int MinHeap::getParentIndex(int index)
{
    return (index - 1) / 2;
}

int MinHeap::getLength()
{
    return length;
}

TEST_CASE("MinHeap test 1")
{
    MinHeap mh;
    mh.push(69);
    mh.push(20);
    mh.push(360);
    mh.push(365);
    mh.push(11);
    mh.push(420);
    mh.push(864);
    mh.push(7);
    mh.push(6);
    mh.push(9);
    mh.push(100);
    mh.push(100);
    mh.push(7777);

    CHECK(mh.getLength() == 13);
    CHECK(mh.pop() == 6);
    CHECK(mh.pop() == 7);
    CHECK(mh.pop() == 9);
    CHECK(mh.pop() == 11);
    CHECK(mh.pop() == 20);
    CHECK(mh.pop() == 69);
    CHECK(mh.pop() == 100);
    CHECK(mh.pop() == 100);
    CHECK(mh.pop() == 360);
    CHECK(mh.pop() == 365);
    CHECK(mh.pop() == 420);
    CHECK(mh.pop() == 864);
    CHECK(mh.pop() == 7777);
}
