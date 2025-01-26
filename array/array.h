#pragma once
#include <stdbool.h>

typedef struct IntArrayList
{
    int *list;
    int cap;
    int size;
} IntArrayList;

IntArrayList* initArrayList(const int capacity);
void destructIntArrayList(IntArrayList* arrayList);
int getElementAt(const IntArrayList* arrayList, const int pos);
bool push(IntArrayList* arrayList, const int element);
int pop(IntArrayList* arrayList);
bool unshift(IntArrayList* arrayList, const int element);
int shift(IntArrayList* arrayList);
void increaseSize(IntArrayList* arrayList);
void decreaseSize(IntArrayList* arrayList);
