#include "./header/stack.h"
#include "./test/test.h"
/*
    LIFO Stack
    Description: A LIFO (Last In, First Out) stack is a linear data structure where the last element added is the first one to be removed.
    Implementation Hint: Use an array or linked list to implement push and pop operations effectively.
*/
TEST_CASE("testing Stack")
{
    Stack<int> stack;
    stack.push(12);
    stack.push(29);
    stack.push(3);
    stack.push(902);
    stack.push(12928);
    stack.push(1);
    stack.push(74);

    CHECK(stack.pop() == 74);
    CHECK(stack.pop() == 1);
    CHECK(stack.pop() == 12928);
    CHECK(stack.pop() == 902);
    CHECK(stack.pop() == 3);
    CHECK(stack.pop() == 29);
    CHECK(stack.pop() == 12);
    CHECK(stack.pop() == std::nullopt);
}
