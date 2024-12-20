#include "../test/test.h"
#include <vector>
#include <optional>
/*
    Max Heap
    Description: A max heap is a complete binary tree where the value of each node is greater than or equal to the values of its children, ensuring the maximum element is at the root.
    Implementation Hint: Implement insertion and deletion while maintaining the heap property using a bottom-up or top-down approach.
*/
class MaxHeap
{
public:
    MaxHeap() : length{0}, items{} {};
    std::optional<int> peek();
    void push(int value);
    std::optional<int> pop();
    int getLength();

private:
    int length;
    std::vector<int> items;
    int getLeftIndex(int index);
    int getRightIndex(int index);
    int getParentIndex(int index);
    void heapifyDown(int index);
    void heapifyUp(int index);
    void swap(int index1, int index2);
};

std::optional<int> MaxHeap::pop()
{
    if (length == 0)
    {
        return std::nullopt;
    }

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

void MaxHeap::push(int value)
{
    items.push_back(value);
    length++;
    heapifyUp(length - 1);
}

void MaxHeap::heapifyUp(int index)
{
    if (index == 0)
    {
        return;
    }

    int indexValue = items.at(index);
    int parentIndex = getParentIndex(index);
    int parentValue = items.at(parentIndex);

    if (indexValue > parentValue)
    {
        swap(index, parentIndex);
        heapifyUp(parentIndex);
    }
}

void MaxHeap::heapifyDown(int index)
{
    if (index >= length)
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
        if (leftValue > rightValue && leftValue > indexValue)
        {
            swap(leftIndex, index);
            return heapifyDown(leftIndex);
        }
        else if (rightValue > leftValue && rightValue > indexValue)
        {
            swap(rightIndex, index);
            return heapifyDown(rightIndex);
        }
    }

    if (rightValue.has_value() && rightValue > indexValue)
    {
        swap(rightIndex, index);
        return heapifyDown(rightIndex);
    }

    if (leftValue.has_value() && leftValue > indexValue)
    {
        swap(leftIndex, index);
        return heapifyDown(leftIndex);
    }
}

std::optional<int> MaxHeap::peek()
{
    if (length == 0)
    {
        return std::nullopt;
    }
    else
    {
        return items.at(0);
    }
}

int MaxHeap::getLeftIndex(int index)
{
    return (2 * index) + 1;
}

int MaxHeap::getRightIndex(int index)
{
    return (2 * index) + 2;
}

int MaxHeap::getParentIndex(int index)
{
    return (index - 1) / 2;
}

int MaxHeap::getLength()
{
    return length;
}

void MaxHeap::swap(int index1, int index2)
{
    int tempValue = items.at(index1);
    items.at(index1) = items.at(index2);
    items.at(index2) = tempValue;
}

TEST_CASE("MaxHeap test 1")
{
    MaxHeap mh;
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
    CHECK(mh.pop() == 7777);
    CHECK(mh.pop() == 864);
    CHECK(mh.peek() == 420);
    CHECK(mh.pop() == 420);
    CHECK(mh.pop() == 365);
    CHECK(mh.pop() == 360);
    CHECK(mh.pop() == 100);
    CHECK(mh.pop() == 100);
    CHECK(mh.peek() == 69);
    CHECK(mh.pop() == 69);
    CHECK(mh.pop() == 20);
    CHECK(mh.pop() == 11);
    CHECK(mh.pop() == 9);
    CHECK(mh.pop() == 7);
    CHECK(mh.pop() == 6);
    CHECK(mh.pop() == std::nullopt);
}

TEST_CASE("MaxHeap test 2")
{
    MaxHeap mh;
    mh.push(1002);
    mh.push(2);
    mh.push(2);
    mh.push(2);
    mh.push(100);
    mh.push(199);
    mh.push(90);
    mh.push(4);
    mh.push(765);
    mh.push(99804);
    mh.push(1000030);
    mh.push(78);
    mh.push(10);
    mh.push(20);
    mh.push(23);
    mh.push(45);
    mh.push(764);
    mh.push(5303);
    mh.push(303);
    mh.push(808);
    mh.push(1909);
    mh.push(2233);
    mh.push(1111);
    mh.push(1); 
    mh.push(2); 
    mh.push(3);
    mh.push(2001);
    mh.push(1999);
    mh.push(7930);
    mh.push(90);
    mh.push(37);
    mh.push(52);
    mh.push(2025);
 
    CHECK(mh.getLength() == 33);
    CHECK(mh.pop() == 1000030);
    CHECK(mh.pop() == 99804);

    mh.push(9999);

    CHECK(mh.peek() == 9999);
    CHECK(mh.pop() == 9999);
    
    mh.push(2234);
    
    CHECK(mh.peek() == 7930);
    CHECK(mh.pop() == 7930);
    CHECK(mh.pop() == 5303);
    CHECK(mh.pop() == 2234);
    CHECK(mh.peek() == 2233);
    CHECK(mh.pop() == 2233);
    CHECK(mh.pop() == 2025);
    CHECK(mh.peek() == 2001);
    CHECK(mh.pop() == 2001);
    CHECK(mh.peek() == 1999);
    CHECK(mh.pop() == 1999);
    CHECK(mh.pop() == 1909);
    CHECK(mh.pop() == 1111);
    CHECK(mh.pop() == 1002);
    CHECK(mh.pop() == 808);
    CHECK(mh.pop() == 765);
    CHECK(mh.pop() == 764);
    CHECK(mh.peek() == 303);
    CHECK(mh.pop() == 303);
    CHECK(mh.pop() == 199);
    CHECK(mh.pop() == 100);
    CHECK(mh.pop() == 90);
    CHECK(mh.peek() == 90);
    CHECK(mh.pop() == 90);

    mh.push(13);

    CHECK(mh.pop() == 78);
    CHECK(mh.pop() == 52);
    CHECK(mh.pop() == 45);
    CHECK(mh.pop() == 37);
    CHECK(mh.pop() == 23);
    CHECK(mh.peek() == 20);
    CHECK(mh.pop() == 20);
    CHECK(mh.peek() == 13);
    CHECK(mh.pop() == 13);
    CHECK(mh.pop() == 10);
    CHECK(mh.pop() == 4);
    CHECK(mh.pop() == 3);
    CHECK(mh.pop() == 2);
    CHECK(mh.pop() == 2);
    CHECK(mh.pop() == 2);
    CHECK(mh.pop() == 2);
    CHECK(mh.peek() == 1);
    CHECK(mh.pop() == 1);

    CHECK(mh.getLength() == 0);
    CHECK(mh.peek() == std::nullopt);
    CHECK(mh.pop() == std::nullopt);
}