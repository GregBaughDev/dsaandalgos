#pragma once
#include <stdbool.h>

typedef struct CircularBuffer
{
    int* list;
    int readIdx;
    int writeIdx;
    int size;
    int count;
} CircularBuffer;

CircularBuffer* initBuffer(int listSize);
bool push(int element, CircularBuffer* buf);
int pop(CircularBuffer* buf);

