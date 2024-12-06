#ifndef QUEUE_H
#define QUEUE_H
#include "./doublylinkedlist.h"
#include <optional>

template <typename T>
class Queue
{
public:
    Queue() : linkedList{} {};
    void enqueue(const T &element);
    void enqueue(const T &&element);
    std::optional<T> dequeue();

private:
    DoublyLinkedList<T> linkedList;
};

template <typename T>
void Queue<T>::enqueue(const T &element)
{
    linkedList.insertAtStart(element);
}

template <typename T>
void Queue<T>::enqueue(const T &&element)
{
    linkedList.insertAtStart(element);
}

template <typename T>
std::optional<T> Queue<T>::dequeue()
{
    return linkedList.removeFromEnd();
}

#endif
