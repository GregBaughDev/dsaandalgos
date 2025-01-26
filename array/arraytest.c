#include "./array.h"
#include <stdio.h>
#include <assert.h>

void test1()
{
    IntArrayList* list = initArrayList(1);

    int LIST_SIZE = 500;

    for (int i = 0; i < LIST_SIZE; i += 5)
    {
        push(list, i);
        push(list, i + 1);
        push(list, i + 2);
        push(list, i + 3);
        push(list, i + 4);
    }

    assert(list->cap == 512);
    assert(list->size == LIST_SIZE);

    for (int j = 0; j < LIST_SIZE; j += 5)
    {
        assert(getElementAt(list, j) == j);
        assert(getElementAt(list, j + 1) == j + 1);
        assert(getElementAt(list, j + 2) == j + 2);
        assert(getElementAt(list, j + 3) == j + 3);
        assert(getElementAt(list, j + 4) == j + 4);
    }

    int currVal = 0;

    while (list->size != 0)
    {
        assert(shift(list) == currVal);
        currVal++;
    }

    destructIntArrayList(list);
    printf("test 1 passed\n");
}

void test2()
{
    IntArrayList* list = initArrayList(5);

    int LIST_SIZE = 10000;

    for (int i = 0; i < LIST_SIZE; i++)
    {
        unshift(list, i);
    }

    int m = LIST_SIZE - 1;
    int n = 0;

    while (m != -1)
    {
        assert(getElementAt(list, n) == m);
        m--;
        n++;
    }

    assert(list->cap == 10240);
    assert(list->size == LIST_SIZE);

    for (int j = LIST_SIZE - 1; j >= 0; j--)
    {
        assert(shift(list) == j);
    }

    unshift(list, 123);
    unshift(list, 456);
    push(list, 789);
    push(list, 1001);

    assert(shift(list) == 456);
    assert(shift(list) == 123);
    assert(pop(list) == 1001);
    assert(pop(list) == 789);

    assert(pop(list) == -1);

    destructIntArrayList(list);
    printf("test 2 passed\n");
}

int main()
{
    test1();
    test2();
    return 0;
}