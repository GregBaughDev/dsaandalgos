#include "./test/test.h"
/*
    Quick Sort
    Description: Quick sort is a divide-and-conquer algorithm that sorts an array by selecting a 'pivot' element and partitioning the other elements into two sub-arrays.
    Implementation Hint: Choose a pivot and rearrange the array such that elements less than the pivot come before it, and those greater come after.
*/
class QuickSort
{
public:
    QuickSort(std::vector<int> list) : itemsList{list} 
    {
        sort();
    };
    int getElement(int pos);
    std::vector<int> getList();

private:
    void sort();
    void pivot(std::vector<int>& list);
    void pivot(std::vector<int>& list, int startPos, int endPos);
    void swap(std::vector<int>& list, int posA, int posB);
    std::vector<int> itemsList;
};

void QuickSort::sort()
{
    if (itemsList.size() < 2) return;
    
    pivot(itemsList);
}

void QuickSort::pivot(std::vector<int>& list)
{
    pivot(list, 0, static_cast<int>(list.capacity() - 1));
}

std::vector<int> QuickSort::getList()
{
    return itemsList;
}

int QuickSort::getElement(int pos)
{
    return itemsList.at(pos);
}

void QuickSort::pivot(std::vector<int>& list, int startPos, int endPos)
{
    if (startPos >= endPos) return;

    int pivot = list[endPos];
    int lowIdx = startPos;
    int highIdx = endPos;

    while (lowIdx < highIdx) 
    {
        while (list[lowIdx] <= pivot && lowIdx < highIdx)
        {
            lowIdx++;
        }

        while (list[highIdx] >= pivot && highIdx > lowIdx)
        {
            highIdx--;
        }
        swap(list, highIdx, lowIdx);
    }
    // move the pivot into position
    swap(list, endPos, highIdx);

    this->pivot(list, startPos, lowIdx - 1);
    this->pivot(list, highIdx + 1, endPos);
}

void QuickSort::swap(std::vector<int>& list, int posA, int posB)
{
    int temp = list[posA];
    list[posA] = list[posB];
    list[posB] = temp;
}

TEST_CASE("testing QuickSort - 1")
{
    QuickSort quickSort({773, 4, 1, 0, 47, 23, 109, 3938, 49402, 20924, 100203, 47, 5, 9, 10, 23894, 23, 654, 876, 3});
    CHECK(quickSort.getElement(0) == 0);
    CHECK(quickSort.getElement(1) == 1);
    CHECK(quickSort.getElement(2) == 3);
    CHECK(quickSort.getElement(3) == 4);
    CHECK(quickSort.getElement(4) == 5);
    CHECK(quickSort.getElement(5) == 9);
    CHECK(quickSort.getElement(6) == 10);
    CHECK(quickSort.getElement(7) == 23);
    CHECK(quickSort.getElement(8) == 23);
    CHECK(quickSort.getElement(9) == 47);
    CHECK(quickSort.getElement(10) == 47);
    CHECK(quickSort.getElement(11) == 109);
    CHECK(quickSort.getElement(12) == 654);
    CHECK(quickSort.getElement(13) == 773);
    CHECK(quickSort.getElement(14) == 876);
    CHECK(quickSort.getElement(15) == 3938);
    CHECK(quickSort.getElement(16) == 20924);
    CHECK(quickSort.getElement(17) == 23894);
    CHECK(quickSort.getElement(18) == 49402);
    CHECK(quickSort.getElement(19) == 100203);
}


