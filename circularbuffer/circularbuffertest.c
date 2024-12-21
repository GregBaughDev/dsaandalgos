#include "./circularbuffer.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void test1();
void test2();

int main()
{
    test1();

    return 0;
}

void test1()
{
    int BUF_SIZE = 100;
    CircularBuffer* buf = initBuffer(BUF_SIZE);
    
    int i, j;
    for (i = 0; i < BUF_SIZE; i++)
    {
        assert(push(i, buf) == true);
    }
    
    assert(push(10, buf) == false);

    for (j = 0; j < BUF_SIZE; j++)
    {
        assert(pop(buf) == j);
    }
    
    assert(pop(buf) == -1);
    printf("Test 1 passed!\n");

    free(buf);
}

void test2()
{
    // to do
}