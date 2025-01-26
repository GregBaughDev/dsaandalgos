#include "./array.h"
#include "stdlib.h"
#include "stdio.h"

IntArrayList* initArrayList(const int capacity)
{
    if (capacity <= 0)
    {
        perror("Capacity invalid. Must be greater than zero\n");
        abort();
    }

    IntArrayList* list = (IntArrayList*)malloc(sizeof(IntArrayList));

    if (list == NULL)
    {
        perror("Array list allocation failed\n");
        abort();
    }

    list->list = (int*)malloc(sizeof(int) * capacity);

    if (list->list == NULL)
    {
        perror("Internal list allocation failed\n");
        abort();
    }

    list->cap = capacity;
    list->size = 0;

    return list;
}

void destructIntArrayList(IntArrayList* arrayList)
{
    free(arrayList->list);
    free(arrayList);
}

int getElementAt(const IntArrayList *arrayList, const int pos)
{
    if (pos < 0 || pos >= arrayList->size)
    {
        perror("Invalid position. Less than 0 or greater than the current size\n");
        abort();
    }

    return *(arrayList->list + pos);
}

bool push(IntArrayList* arrayList, const int element)
{
    if (arrayList->size + 1 == arrayList->cap)
    {
        increaseSize(arrayList);
    }

    *(arrayList->list + arrayList->size++) = element;
    return true;
}

int pop(IntArrayList* arrayList)
{
    if (arrayList->size == 0)
    {
        return -1;
    }

    arrayList->size--;

    if (arrayList->size > 0 && arrayList->size == arrayList->cap / 2)
    {
        decreaseSize(arrayList);
    }

    return *(arrayList->list + arrayList->size);
}

bool unshift(IntArrayList* arrayList, const int element)
{
    if (arrayList->size + 1 == arrayList->cap)
    {
        increaseSize(arrayList);
    }

    for (int i = arrayList->size; i > 0; i--)
    {
        *(arrayList->list + i) = *(arrayList->list + (i - 1));
    }

    *arrayList->list = element;
    arrayList->size++;

    return true;
}

void increaseSize(IntArrayList* arrayList)
{
    arrayList->list = (int*)realloc(arrayList->list, sizeof(int) * (arrayList->cap * 2));

    if (arrayList->list == NULL)
    {
        perror("Array list size increase failed\n");
        abort();
    }

    arrayList->cap = arrayList->cap * 2;
    printf("Size increased -> %d\n", arrayList->cap);
}

void decreaseSize(IntArrayList* arrayList)
{
    arrayList->list = (int*)realloc(arrayList->list, sizeof(int) * (arrayList->cap / 2));

    if (arrayList->list == NULL)
    {
        perror("Array list size decrease failed\n");
        abort();
    }

    arrayList->cap = arrayList->cap / 2;
    printf("Size decreased -> %d\n", arrayList->cap);
}

int shift(IntArrayList* arrayList)
{
    int returnVal = *arrayList->list;

    for (int i = 0; i < arrayList->size; i++)
    {
        *(arrayList->list + i) = *(arrayList->list + (i + 1));
    }

    arrayList->size--;

    if (arrayList->size > 0 && arrayList->size == arrayList->cap / 2)
    {
        decreaseSize(arrayList);
    }

    return returnVal;
}





