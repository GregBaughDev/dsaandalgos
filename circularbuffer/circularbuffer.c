#include "./circularbuffer.h"
#include "stdlib.h"
#include "stdio.h"

CircularBuffer* initBuffer(int listSize)
{
    CircularBuffer* buf = malloc(sizeof(CircularBuffer));

    if (buf == NULL)
    {
        printf("Buffer allocation failed\n");
        exit(1);
    }

    buf->list = malloc(listSize * sizeof(int));

    if (buf->list == NULL)
    {
        printf("List allocation failed\n");
        exit(1);
    }

    buf->readIdx = buf->writeIdx = 0;
    buf->count = 0;
    buf->size = listSize;

    return buf;
}

bool push(int element, CircularBuffer* buf)
{
    if (buf->count == buf->size)
    {   
        return false;
    }

    buf->list[buf->writeIdx] = element;
    buf->count++;
    buf->writeIdx++;

    if (buf->writeIdx == buf->size)
    {
        buf->writeIdx = 0;
    }

    return true;
}

int pop(CircularBuffer* buf)
{
    if (buf->count == 0)
    {
        // assuming only unsigned ints are being used
        return -1;
    }

    int value = buf->list[buf->readIdx];
    buf->readIdx++;
    buf->count--;

    if (buf->readIdx == buf->size)
    {
        buf->readIdx = 0;
    }

    return value;
}


