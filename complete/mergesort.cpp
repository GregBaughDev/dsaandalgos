#include "../test/test.h"
/*
    Merge Sort
    Description: Merge sort is a divide-and-conquer algorithm that sorts an array by recursively dividing it into halves, sorting them, and merging them back together.
    Implementation Hint: Use recursion to divide the array and merge two sorted halves while maintaining order.
*/
class MergeSort
{
public:
    MergeSort(std::vector<int> list) : itemsList{list} 
    {
        sort();
    };
    int getElement(int pos);
    const std::vector<int> getList();

private:
    void sort();
    std::vector<int> itemsList;
    void divide(std::vector<int>& itemsList);
    void merge(std::vector<int>& originalList, std::vector<int>& leftItemsList, std::vector<int>& rightItemsList);
};

void MergeSort::divide(std::vector<int>& itemsList)
{
    if (itemsList.size() == 1) return;

    int midpoint = itemsList.size() / 2;
    std::vector<int> leftList = std::vector<int>(midpoint);
    std::vector<int> rightList = std::vector<int>(itemsList.size() - midpoint);

    int i, j;
    for (i = 0; i < midpoint; i++)
    {
        leftList[i] = itemsList[i];
    }

    for (j = midpoint; j < itemsList.size(); j++)
    {
        rightList[j - midpoint] = itemsList[j];
    }

    divide(leftList);
    divide(rightList);

    merge(itemsList, leftList, rightList);
}

void MergeSort::sort()
{   
    if (itemsList.size() < 2) return; 

    divide(itemsList);
}

const std::vector<int> MergeSort::getList()
{
    return itemsList;
}

void MergeSort::merge(std::vector<int>& originalList, std::vector<int>& leftItemsList, std::vector<int>& rightItemsList)
{
    // a while loop to replace the items in the original list 
    int lPos{0};
    int rPos{0};
    int i{0};

    while (lPos < leftItemsList.size() && rPos < rightItemsList.size())
    {
        if (leftItemsList[lPos] <= rightItemsList[rPos])
        {
            originalList[i] = leftItemsList[lPos];
            lPos++;
        }
        else
        {
            originalList[i] = rightItemsList[rPos];
            rPos++;
        }

        i++;
    }

    while (lPos < leftItemsList.size())
    {
        originalList[i] = leftItemsList[lPos];
        lPos++;
        i++;
    }

    while (rPos < rightItemsList.size())
    {
        originalList[i] = rightItemsList[rPos];
        rPos++;
        i++;
    }
}

int MergeSort::getElement(int pos)
{
    return itemsList.at(pos);
}

TEST_CASE("testing MergeSort - 1")
{

    MergeSort mergeSort{{39, 2, 930, 56, 9039, 54, 1, 27573, 9, 69}};
    CHECK(mergeSort.getElement(0) == 1);
    CHECK(mergeSort.getElement(1) == 2);
    CHECK(mergeSort.getElement(2) == 9);
    CHECK(mergeSort.getElement(3) == 39);
    CHECK(mergeSort.getElement(4) == 54);
    CHECK(mergeSort.getElement(5) == 56);
    CHECK(mergeSort.getElement(6) == 69);
    CHECK(mergeSort.getElement(7) == 930);
    CHECK(mergeSort.getElement(8) == 9039);
    CHECK(mergeSort.getElement(9) == 27573);
}

TEST_CASE("testing MergeSort - 2")
{
    MergeSort mergeSort2{{1, 2, 3, 4, 5, 10, 9, 8, 7, 6}};
    CHECK(mergeSort2.getElement(0) == 1);
    CHECK(mergeSort2.getElement(1) == 2);
    CHECK(mergeSort2.getElement(2) == 3);
    CHECK(mergeSort2.getElement(3) == 4);
    CHECK(mergeSort2.getElement(4) == 5);
    CHECK(mergeSort2.getElement(5) == 6);
    CHECK(mergeSort2.getElement(6) == 7);
    CHECK(mergeSort2.getElement(7) == 8);
    CHECK(mergeSort2.getElement(8) == 9);
    CHECK(mergeSort2.getElement(9) == 10);
}  