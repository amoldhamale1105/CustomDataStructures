#pragma once
#include <iostream>
#include <Vector.hpp>

template <typename T>
class Stack
{
    class Node
    {
        T data;
        Node* next;

    public:
        Node(const T& data) : data(data), next(nullptr) {}
        ~Node() { if (next != nullptr) delete next; }
    
        friend class Stack<T>;
    };

    Node* head;
    void insertAtBottom(const T& data);

public:
    Stack() : head(nullptr) {}
    Stack(Stack<T>& other);
    virtual ~Stack() { if (head != nullptr) delete head; }
    void push(const T& data);
    T pop();
    T top() const;
    size_t depth() const;
    void clear();
    bool isEmpty() const;
    void reverse();

    void operator=(Stack<T>& other);
};

/* Stack Impl */

template <typename T>
Stack<T>::Stack(Stack<T>& other) : head(nullptr)
{
    Vector<T> stackContainer;

    while (!other.isEmpty())
    {
        stackContainer.push_back(other.pop());
    }

    while (!stackContainer.isEmpty())
    {
        T currentElement = stackContainer.pop_back();
        this->push(currentElement);
        other.push(currentElement);
    }
}

template <class T>
void Stack<T>::operator=(Stack<T>& other)
{
    head = nullptr;
    Vector<T> stackContainer;

    while (!other.isEmpty())
    {
        stackContainer.push_back(other.pop());
    }

    while (!stackContainer.isEmpty())
    {
        T currentElement = stackContainer.pop_back();
        this->push(currentElement);
        other.push(currentElement);
    }
}

template <class T>
void Stack<T>::push(const T& data)
{
    Node* node = new Node(data);
    node->next = head;
    head = node;
}

template <class T>
T Stack<T>::pop()
{
    T retVal{};

    if (head != nullptr){
        Node* node = head;
        retVal = node->data;
        head = node->next;
        node->next = nullptr;
        delete node;
    }

    return retVal;
}

template <class T>
T Stack<T>::top() const
{
    return head != nullptr ? head->data : T{};
}

template <class T>
size_t Stack<T>::depth() const
{
    size_t count{0};
    Node* currentNode = head;
    
    while (currentNode != nullptr)
    {
        count++;
        currentNode = currentNode->next;
    }

    return count;
}

template <class T>
void Stack<T>::clear()
{
    if (head != nullptr)
        delete head;
    head = nullptr;
}

template <class T>
bool Stack<T>::isEmpty() const
{
    return head == nullptr;
}

template <class T>
void Stack<T>::reverse()
{
    //Base case
    if (depth() == 1)
        return;

    //Rec case
    T topElement = pop();
    reverse();
    insertAtBottom(topElement);
}

template <class T>
void Stack<T>::insertAtBottom(const T& data)
{
    //Base case
    if (isEmpty()){
        push(data);
        return;
    }

    //Rec case
    T topElement = pop();
    insertAtBottom(data);
    push(topElement);
}
