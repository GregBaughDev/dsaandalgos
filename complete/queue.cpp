#include "../header/queue.h"
#include "../test/test.h"
/*
    FIFO Queue
    Description: A FIFO (First In, First Out) queue is a linear data structure that allows adding elements to the back and removing them from the front.
    Implementation Hint: Use an array or linked list to implement the enqueue and dequeue operations efficiently.
*/
TEST_CASE("testing Queue")
{
    Queue<int> queue;
    queue.enqueue(12);
    queue.enqueue(29);
    queue.enqueue(3);
    queue.enqueue(902);
    queue.enqueue(12928);
    queue.enqueue(1);
    queue.enqueue(74);
    int ft = 43;
    queue.enqueue(ft);

    CHECK(queue.dequeue() == 12);
    CHECK(queue.dequeue() == 29);
    CHECK(queue.dequeue() == 3);
    CHECK(queue.dequeue() == 902);
    CHECK(queue.dequeue() == 12928);
    CHECK(queue.dequeue() == 1);
    CHECK(queue.dequeue() == 74);
    CHECK(queue.dequeue() == ft);
    CHECK(queue.dequeue() == std::nullopt);
}

