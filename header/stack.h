#ifndef STACK_H
#define STACK_H
#include "./doublylinkedlist.h"
#include <optional>

template <typename T>
class Stack
{
public:
    Stack() : linkedList{} {};
    void push(const T &element);
    void push(const T &&element);
    std::optional<T> pop();

private:
    DoublyLinkedList<T> linkedList;
};

template <typename T>
void Stack<T>::push(const T &element)
{
    linkedList.insertAtStart(element);
}

template <typename T>
void Stack<T>::push(const T &&element)
{
    linkedList.insertAtStart(element);
}

template <typename T>
std::optional<T> Stack<T>::pop()
{
    return linkedList.removeFromStart();
}

#endif
