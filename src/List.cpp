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
    if (position <= 0){
        push_front(data);
        return;
    }

    Node* trailingNodeAddr = head;
    for(auto jump = 0; jump < position-1; ++jump)
    {
        trailingNodeAddr = trailingNodeAddr->next;
        if (trailingNodeAddr == nullptr){
            push_back(data);
            return;
        }
    }

    Node* node = new Node(data);
    node->next = trailingNodeAddr->next;
    trailingNodeAddr->next = node;
}

template <class T>
T List<T>::find(const int& position) const
{
    if (position <= 0)
        return head->data;

    Node* currentNode = head->next;
    for(auto i = 1; i < position; ++i)
    {
        if (currentNode == nullptr)
            return tail->data;
        currentNode = currentNode->next;
    }
    return currentNode->data;
}

template <class T>
int List<T>::position(const T& data) const
{
    Node* currentNode = head;
    int index = 0;
    while (currentNode != nullptr)
    {
        if (currentNode->data == data)
            return index;
        currentNode = currentNode->next;
        index++;
    }
    return -1;
}

template <class T>
int List<T>::recursive_search_helper(Node* currentNode, const T& key)
{
    if (currentNode == nullptr)
        return -1;
    if (currentNode->data == key)
        return 0;

    int position = recursive_search_helper(currentNode->next, key);
    if (position == -1)
        return -1;
    return position+1;
}

template <class T>
int List<T>::recursive_search(const T& data)
{
    return recursive_search_helper(head, data);
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