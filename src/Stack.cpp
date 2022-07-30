#ifndef TEMPLATE_METHODS
#include <Stack.hpp>

#else

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
void Stack<T>::clear()
{
    if (head != nullptr)
        delete head;
    head = nullptr;
}

#endif

