#include "./test/test.h"
/*
    Bubble Sort
    Description: Bubble sort is a simple sorting algorithm that repeatedly steps through the list, compares adjacent elements, and swaps them if they are in the wrong order.
    Implementation Hint: Use a nested loop to repeatedly pass through the array until no swaps are needed.
*/
class BubbleSort
{
public:
    BubbleSort(std::vector<int> list) : itemsList{list}
    {
        sort();
    };
    int getElement(int pos);
private:
    void sort();
    std::vector<int> itemsList;
};

int BubbleSort::getElement(int pos)
{
    return itemsList.at(pos);
}

void BubbleSort::sort()
{
    int switches;
    while (true)
    {
        switches = 0;
        int i;
        for (i = 0; i < itemsList.size(); i++)
        {
            if (i + 1 != itemsList.size() && itemsList.at(i) > itemsList.at(i + 1))
            {
                int temp = itemsList.at(i);
                itemsList[i] = itemsList[i + 1];
                itemsList[i + 1] = temp;
                switches++;
            }
        }
        if (switches == 0)
        {
            break;
        }
    }
}

TEST_CASE("testing BubbleSort - 1")
{
    BubbleSort bubbleSort{{67, 34, 29, 97, 182, 4, 2, 9, 392, 23984, 293, 48292, 9, 234, 1010}};
    CHECK(bubbleSort.getElement(0) == 2); 
    CHECK(bubbleSort.getElement(1) == 4); 
    CHECK(bubbleSort.getElement(2) == 9); 
    CHECK(bubbleSort.getElement(3) == 9); 
    CHECK(bubbleSort.getElement(4) == 29); 
    CHECK(bubbleSort.getElement(5) == 34); 
    CHECK(bubbleSort.getElement(6) == 67); 
    CHECK(bubbleSort.getElement(7) == 97); 
    CHECK(bubbleSort.getElement(8) == 182); 
    CHECK(bubbleSort.getElement(9) == 234); 
    CHECK(bubbleSort.getElement(10) == 293); 
    CHECK(bubbleSort.getElement(11) == 392); 
    CHECK(bubbleSort.getElement(12) == 1010); 
    CHECK(bubbleSort.getElement(13) == 23984); 
    CHECK(bubbleSort.getElement(14) == 48292); 
}

TEST_CASE("testing BubbleSort - 2")
{
    BubbleSort bubbleSort{{10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}};
    CHECK(bubbleSort.getElement(0) == 0);
    CHECK(bubbleSort.getElement(1) == 1);
    CHECK(bubbleSort.getElement(2) == 2);
    CHECK(bubbleSort.getElement(3) == 3);
    CHECK(bubbleSort.getElement(4) == 4);
    CHECK(bubbleSort.getElement(5) == 5);
    CHECK(bubbleSort.getElement(6) == 6);
    CHECK(bubbleSort.getElement(7) == 7);
    CHECK(bubbleSort.getElement(8) == 8);
    CHECK(bubbleSort.getElement(9) == 9);
    CHECK(bubbleSort.getElement(10) == 10);
}
