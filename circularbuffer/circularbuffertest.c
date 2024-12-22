#include "./circularbuffer.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void test1();
void test2();

int main()
{
    test1();
    test2();

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
    CircularBuffer *buf = initBuffer(12);

    assert(push(30, buf) == true);
    assert(push(60, buf) == true);
    assert(push(33, buf) == true);
    assert(push(11, buf) == true);

    assert(pop(buf) == 30);
    assert(pop(buf) == 60);

    assert(push(104, buf) == true);
    assert(push(9, buf) == true);
    assert(push(693, buf) == true);

    assert(pop(buf) == 33);
    assert(pop(buf) == 11);
    assert(pop(buf) == 104);
    assert(pop(buf) == 9);
    assert(pop(buf) == 693);
    assert(pop(buf) == -1);

    assert(push(10, buf) == true);
    assert(push(11, buf) == true);
    assert(push(32, buf) == true);
    assert(push(33, buf) == true);
    assert(push(44, buf) == true);
    assert(push(55, buf) == true);
    assert(push(1, buf) == true);
    assert(push(90, buf) == true);
    assert(push(357, buf) == true);
    assert(push(3, buf) == true);
    assert(push(56, buf) == true);
    assert(push(4, buf) == true);

    assert(push(68, buf) == false);
    assert(push(34, buf) == false);
    assert(push(985, buf) == false);

    assert(pop(buf) == 10);
    assert(pop(buf) == 11);
    assert(pop(buf) == 32);
    assert(pop(buf) == 33);
    assert(pop(buf) == 44);
    assert(pop(buf) == 55);
    assert(pop(buf) == 1);
    assert(pop(buf) == 90);
    assert(pop(buf) == 357);

    assert(push(44, buf) == true);
    assert(pop(buf) == 3);
    assert(pop(buf) == 56);
    assert(pop(buf) == 4);
    assert(pop(buf) == 44);
    assert(pop(buf) == -1);
    assert(pop(buf) == -1);
    assert(pop(buf) == -1);
    printf("Test 2 passed!\n");

    free(buf);
}