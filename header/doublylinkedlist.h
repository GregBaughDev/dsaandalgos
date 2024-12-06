#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H
#include <optional>
#include <iostream>

template <typename T>
class DoublyLinkedList
{
public:
    DoublyLinkedList() {};
    ~DoublyLinkedList()
    {
        clear();
    };
    DoublyLinkedList(const DoublyLinkedList &rhs) // copy constructor
    {
        Node *currentNode = rhs.firstNode;
        while (currentNode != nullptr)
        {
            insertAtEnd(currentNode->getElement());
            currentNode = currentNode->getNextNode();
        }
    };
    DoublyLinkedList &operator=(const DoublyLinkedList &rhs) // copy assignment
    {
        if (this != &rhs)
        {
            // clear out the existing data
            this->clear();

            // copy over the passed in data
            Node *currentNode = rhs.firstNode;

            while (currentNode != nullptr)
            {
                insertAtEnd(currentNode->getElement());
                currentNode = currentNode->getNextNode();
            }
        }
        return *this;
    }
    DoublyLinkedList(DoublyLinkedList &&rhs) noexcept // move constructor
    {
        this->firstNode = std::exchange(rhs.firstNode, nullptr);
        this->lastNode = std::exchange(rhs.lastNode, nullptr);
        this->length = std::exchange(rhs.length, 0);
    };
    DoublyLinkedList &operator=(DoublyLinkedList &&rhs) noexcept // move assignment
    {
        if (this != &rhs)
        {
            this->clear();
            this->firstNode = std::exchange(rhs.firstNode, nullptr);
            this->lastNode = std::exchange(rhs.lastNode, nullptr);
            this->length = std::exchange(rhs.length, 0);
        }

        return *this;
    };
    // the below 2 methods will make copies if an rvalue is passed in
    // to overcome this we can overload the method and duplicate
    // to optimise for rvalues
    void insertAtEnd(const T &element);
    void insertAtStart(const T &element);
    bool search(const T &element) const;
    std::optional<T> remove(const T &element);
    std::optional<T> removeFromStart();
    std::optional<T> removeFromEnd();
    int getLength() const;
    void printElements() const;

private:
    class Node
    {
    public:
        Node(T element) : element{element} {};
        void setNextNode(Node *newNextNode);
        void setPrevNode(Node *newPrevNode);
        Node *getNextNode() const;
        Node *getPrevNode() const;
        T getElement() const;

    private:
        T element;
        Node *nextNode = nullptr;
        Node *prevNode = nullptr;
    };
    Node *firstNode = nullptr;
    Node *lastNode = nullptr;
    void clear();
    int length = 0;
};

template <typename T>
void DoublyLinkedList<T>::insertAtEnd(const T &element)
{
    Node *newNode = new Node(element);

    if (!firstNode)
    {
        firstNode = newNode;
    }
    else
    {
        newNode->setPrevNode(lastNode);
        lastNode->setNextNode(newNode);
    }

    lastNode = newNode;
    length++;
}

template <typename T>
void DoublyLinkedList<T>::insertAtStart(const T &element)
{
    Node *newNode = new Node(element);

    if (firstNode == nullptr)
    {
        firstNode = lastNode = newNode;
    }
    else
    {
        newNode->setNextNode(firstNode);
        firstNode->setPrevNode(newNode);
        firstNode = newNode;
    }

    length++;
}

template <typename T>
bool DoublyLinkedList<T>::search(const T &element) const
{
    Node *currentNode = firstNode;

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

template <typename T>
std::optional<T> DoublyLinkedList<T>::remove(const T &element)
{
    if (firstNode == nullptr)
    {
        return std::nullopt;
    }

    if (firstNode->getElement() == element)
    {
        return removeFromStart();
    }

    if (lastNode->getElement() == element)
    {
        return removeFromEnd();
    }

    Node *currentNode = firstNode->getNextNode();

    while (currentNode != nullptr)
    {
        if (currentNode->getElement() == element)
        {
            currentNode->getPrevNode()->setNextNode(currentNode->getNextNode());
            currentNode->getNextNode()->setPrevNode(currentNode->getPrevNode());

            delete currentNode;
            length--;
            return element;
        }
        else
        {
            currentNode = currentNode->getNextNode();
        }
    }

    return std::nullopt;
}

template <typename T>
std::optional<T> DoublyLinkedList<T>::removeFromStart()
{
    if (firstNode == nullptr)
    {
        return std::nullopt;
    }

    T element = firstNode->getElement();
    length--;

    if (length == 0)
    {
        firstNode = lastNode = nullptr;
    }
    else
    {
        firstNode = firstNode->getNextNode();
        firstNode->setPrevNode(nullptr);
    }

    return element;
}

template <typename T>
std::optional<T> DoublyLinkedList<T>::removeFromEnd()
{
    if (firstNode == nullptr)
    {
        return std::nullopt;
    }

    if (firstNode == lastNode)
    {
        T value = firstNode->getElement();
        delete firstNode;
        firstNode = lastNode = nullptr;
        length = 0;
        return value;
    }

    T element = lastNode->getElement();

    lastNode = lastNode->getPrevNode();
    lastNode->setNextNode(nullptr);

    length--;
    return element;
}

template <typename T>
int DoublyLinkedList<T>::getLength() const
{
    return length;
}

template <typename T>
void DoublyLinkedList<T>::printElements() const
{
    std::cout << "[" << this << "] Elements -> ";

    Node *currentNode = firstNode;

    while (currentNode != nullptr)
    {
        std::cout << currentNode->getElement() << " ";
        currentNode = currentNode->getNextNode();
    }

    std::cout << "\n";
}

template <typename T>
void DoublyLinkedList<T>::clear()
{
    while (firstNode != nullptr)
    {
        Node *temp = firstNode;
        firstNode = firstNode->getNextNode();
        delete temp;
    }

    firstNode = lastNode = nullptr;
    length = 0;
}

template <typename T>
void DoublyLinkedList<T>::Node::setNextNode(Node *newNextNode)
{
    this->nextNode = newNextNode;
}

template <typename T>
void DoublyLinkedList<T>::Node::setPrevNode(Node *newPrevNode)
{
    this->prevNode = newPrevNode;
}

template <typename T>
DoublyLinkedList<T>::Node *DoublyLinkedList<T>::Node::getNextNode() const
{
    return this->nextNode;
}

template <typename T>
DoublyLinkedList<T>::Node *DoublyLinkedList<T>::Node::getPrevNode() const
{
    return this->prevNode;
}

template <typename T>
T DoublyLinkedList<T>::Node::getElement() const
{
    return this->element;
}

#endif
