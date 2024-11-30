#include "./test/test.h"
#include <iostream>
/*
    Singly Linked List
    Description: A singly linked list is a data structure consisting of nodes, where each node contains data and a pointer to the next node in the sequence.
    Implementation Hint: Handle insertions and deletions by manipulating the next pointers of the nodes accordingly.
*/
class SinglyLinkedList
{
public:
    SinglyLinkedList() {};
    ~SinglyLinkedList()
    {
        while (firstNode != nullptr)
        {
            Node* temp = firstNode;
            firstNode = firstNode->getNextNode();
            delete temp;
        }

        firstNode = nullptr;
        lastNode = nullptr;
        length = 0;
    };
    void insertAtEnd(int element);
    void insertAtStart(int element);
    bool search(int element) const;
    int remove(int element);
    int removeFromStart();
    int removeFromEnd();
    int getLength() const;
    void printElements() const;
private:
    class Node
    {
    public:
        Node(int element) : element{element} {};
        void setNextNode(Node* newNextNode);
        Node* getNextNode();
        int getElement();
    private:
        int element;
        Node* nextNode = nullptr;
    };
    Node* firstNode = nullptr;
    Node* lastNode = nullptr;
    int length = 0;
};

void SinglyLinkedList::insertAtEnd(int element)
{
    Node* newNode = new Node(element);

    if (!firstNode)
    {
        firstNode = newNode;
    }
    else 
    {
        lastNode->setNextNode(newNode);
    }
    
    lastNode = newNode;
    length++;
}

void SinglyLinkedList::insertAtStart(int element)
{
    Node* newNode = new Node(element);

    if (firstNode == nullptr)
    {
        firstNode = lastNode = newNode;
    }
    else 
    {
        newNode->setNextNode(firstNode);
        firstNode = newNode;
    }

    length++;
}

bool SinglyLinkedList::search(int element) const
{
    Node* currentNode = firstNode;

    while (currentNode != nullptr)
    {
        if (currentNode->getElement() == element)
        {
            return true;
        } 
        else 
        {
            currentNode = currentNode->getNextNode();
        }
    }
    
    return false;
}

int SinglyLinkedList::remove(int element)
{
    if (firstNode == nullptr)
    {
        return -1;
    }

    if (firstNode->getElement() == element)
    {
        Node* nodeToDelete = firstNode;

        if (firstNode->getNextNode() != nullptr)
        {
            firstNode = firstNode->getNextNode();
        }
        else
        {
            firstNode = nullptr;
            lastNode = nullptr;
        }

        delete nodeToDelete;
        length--;
        return element;
    }

    Node* currentNode = firstNode->getNextNode();
    Node* prevNode = firstNode;

    while (currentNode != nullptr)
    {
        if (currentNode->getElement() == element)
        {
            Node* nodeToDelete = currentNode;
            prevNode->setNextNode(currentNode->getNextNode());

            delete nodeToDelete;
            length--;
            return element;
        }
        else
        {
            currentNode = currentNode->getNextNode();
            prevNode = prevNode->getNextNode();
        }
    }

    return -1;
}

int SinglyLinkedList::removeFromStart()
{
    if (firstNode == nullptr)
    {
        return -1;
    }

    Node* nodeToDelete = firstNode;
    int nodeToDeleteValue = nodeToDelete->getElement();

    firstNode = firstNode->getNextNode();

    delete nodeToDelete;
    length--;

    if (length == 0)
    {
        firstNode = nullptr;
        lastNode = nullptr;
    }

    return nodeToDeleteValue;
}

int SinglyLinkedList::removeFromEnd()
{
    if (firstNode == nullptr)
    {
        return -1;
    }

    if (firstNode == lastNode)
    {
        int value = firstNode->getElement();
        delete firstNode;
        firstNode = lastNode = nullptr;
        length = 0;
        return value;
    }

    Node* penultimateNode = firstNode;

    while (penultimateNode->getNextNode() != lastNode)
    {
        penultimateNode = penultimateNode->getNextNode();
    }

    Node* nodeToDelete = lastNode;
    int nodeToDeleteValue = nodeToDelete->getElement();
    lastNode = penultimateNode;
    lastNode->setNextNode(nullptr);

    delete nodeToDelete;
    length--;
    return nodeToDeleteValue;
}

int SinglyLinkedList::getLength() const
{
    return length;
}

void SinglyLinkedList::printElements() const
{
    Node* currentNode = firstNode;
    
    std::cout << "Elements:\n";

    int i = 0;
    while (i < length)
    {
        std::cout << currentNode->getElement() << "\n";
        currentNode = currentNode->getNextNode();
        i++;
    }

    std::cout << "******\n";
}

void SinglyLinkedList::Node::setNextNode(Node* newNextNode)
{
    this->nextNode = newNextNode;
}

SinglyLinkedList::Node* SinglyLinkedList::Node::getNextNode()
{
    return this->nextNode;
}

int SinglyLinkedList::Node::getElement()
{
    return this->element;
}

TEST_CASE("testing SinglyLinkedList - 1")
{
    SinglyLinkedList sLL;
    sLL.insertAtEnd(1);
    sLL.insertAtEnd(45);
    sLL.insertAtEnd(3);
    sLL.insertAtEnd(198);
    sLL.insertAtEnd(9482);
    sLL.insertAtEnd(10293);
    sLL.insertAtEnd(43);
    
    CHECK(sLL.search(1) == true);
    CHECK(sLL.search(43) == true);
    CHECK(sLL.search(45) == true);
    CHECK(sLL.search(10293) == true);
    CHECK(sLL.search(3) == true);
    CHECK(sLL.search(9482) == true);
    CHECK(sLL.search(198) == true);
    CHECK(sLL.getLength() == 7);

    CHECK(sLL.search(420) == false);
    CHECK(sLL.search(69) == false);
    CHECK(sLL.search(37) == false);

    CHECK(sLL.remove(45) == 45);
    CHECK(sLL.remove(3) == 3);
    CHECK(sLL.getLength() == 5);

    CHECK(sLL.remove(10293) == 10293);
    CHECK(sLL.remove(1) == 1);
    CHECK(sLL.remove(43) == 43);
    CHECK(sLL.getLength() == 2);
    CHECK(sLL.remove(9482) == 9482);
    CHECK(sLL.remove(198) == 198);
    CHECK(sLL.getLength() == 0);

    CHECK(sLL.remove(123) == -1);
    CHECK(sLL.remove(456) == -1);
    CHECK(sLL.getLength() == 0);
}

TEST_CASE("testing SinglyLinkedList - 2")
{
    SinglyLinkedList sLL;
    sLL.insertAtEnd(20);
    sLL.insertAtStart(10);
    sLL.insertAtEnd(40);
    sLL.insertAtStart(104);
    sLL.insertAtEnd(123);
    sLL.insertAtEnd(987);
    sLL.insertAtStart(943);
    sLL.insertAtStart(1023);
    sLL.insertAtEnd(69);
    CHECK(sLL.getLength() == 9);

    CHECK(sLL.removeFromEnd() == 69);
    CHECK(sLL.removeFromStart() == 1023);
    CHECK(sLL.getLength() == 7);

    CHECK(sLL.removeFromEnd() == 987);
    CHECK(sLL.removeFromStart() == 943);
    CHECK(sLL.getLength() == 5);

    CHECK(sLL.removeFromEnd() == 123);
    CHECK(sLL.removeFromStart() == 104);
    CHECK(sLL.getLength() == 3);

    CHECK(sLL.removeFromEnd() == 40);
    CHECK(sLL.removeFromStart() == 10);
    CHECK(sLL.removeFromStart() == 20);
    CHECK(sLL.getLength() == 0);

    sLL.insertAtEnd(432);
    sLL.insertAtStart(9872);
    sLL.insertAtEnd(123);
    
    CHECK(sLL.getLength() == 3);
    CHECK(sLL.removeFromEnd() == 123);
    CHECK(sLL.removeFromEnd() == 432);
    CHECK(sLL.removeFromEnd() == 9872);
    CHECK(sLL.getLength() == 0);
}
