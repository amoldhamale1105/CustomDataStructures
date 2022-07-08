#ifndef TEMPLATE_METHODS
#include <List.hpp>

#else

template <class T>
template <class U>
void List<T>::push_front(U&& data)
{
    if (head == nullptr){
        Node* node = new Node(std::forward<U>(data));
        head = tail = node;
    }
    else{
        Node* node = new Node(std::forward<U>(data));
        node->next = head;
        head = node;
    }
}

template <class T>
template <class U>
void List<T>::push_back(U&& data)
{
    if (head == nullptr){
        Node* node = new Node(std::forward<U>(data));
        head = tail = node;
    }
    else{
        Node* node = new Node(std::forward<U>(data));
        tail->next = node;
        tail = node;
    }
}

template <class T>
T List<T>::front() const
{
    return head->data;
}

template <class T>
Vector<T> List<T>::get_list() const
{
    Node* currentNode = head;
    Vector<T> list;
    while (currentNode != nullptr)
    {
        list.push_back(currentNode->data);
        currentNode = currentNode->next;
    }
    
    return list;
}


#endif