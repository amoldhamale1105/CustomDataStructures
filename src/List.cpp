#ifndef TEMPLATE_METHODS
#include <List.hpp>

#else

template <class T>
void List<T>::push_front(const T& data)
{
    if (head == nullptr){
        Node* node = new Node(data);
        head = tail = node;
    }
    else{
        Node* node = new Node(data);
        node->next = head;
        head = node;
    }
}

template <class T>
void List<T>::push_back(const T& data)
{
    if (head == nullptr){
        Node* node = new Node(data);
        head = tail = node;
    }
    else{
        Node* node = new Node(data);
        tail->next = node;
        tail = node;
    }
}

template <class T>
void List<T>::insert(const T& data, const int& position)
{
    if (position == 0){
        push_front(data);
        return;
    }

    Node* trailingNodeAddr = head;
    for(auto jump = 0; jump < position-1; ++jump)
    {
        trailingNodeAddr = trailingNodeAddr->next;
    }

    Node* node = new Node(data);
    node->next = trailingNodeAddr->next;
    trailingNodeAddr->next = node;
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