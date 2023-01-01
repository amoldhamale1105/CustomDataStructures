#ifndef TEMPLATE_METHODS
#include <List.hpp>

#else

template <class T>
List<T>::~List()
{
    if (head != nullptr)
        delete head;
}

template <class T>
List<T>::List(const List<T>& otherList) : head(nullptr), tail(nullptr)
{
    Node* otherNode = otherList.head;

    while (otherNode != nullptr)
    {
        push_back(otherNode->data);
        otherNode = otherNode->next;
    }
}

template <class T>
void List<T>::operator=(const List<T>& otherList)
{
    Node* otherNode = otherList.head;
    Node* node;

    if (otherNode != nullptr){
        if (head == nullptr){
            head = new Node(otherNode->data);
            tail = head;
        }
        else
            head->data = otherNode->data;
        Node* node = head->next;
        otherNode = otherNode->next;

        while (otherNode != nullptr)
        {
            if (node == nullptr){
                node = new Node(otherNode->data);
                tail->next = node;
                tail = node;
            }
            else
                node->data = otherNode->data;
            node = node->next;
            otherNode = otherNode->next;
        }
    }
    else{
        if (head != nullptr){
            delete head;
            head = tail = nullptr;
        }
    }
}

template <class T>
size_t List<T>::size() const
{
    Node* currentNode = head;
    size_t totalNodes{0};
    while (currentNode != nullptr)
    {
        totalNodes++;
        currentNode = currentNode->next;
    }

    return totalNodes;
}

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
T List<T>::pop_front()
{
    T retVal{};
    
    if (head != nullptr){
        Node *node = head->next;
        retVal = head->data;
        head->next = nullptr;
        delete head;
        head = node;
    }
    return retVal;
}

template <class T>
T List<T>::pop_back()
{
    T retVal{};
    
    if (head != nullptr){
        Node* currentNode = head;
        while (currentNode->next != tail)
        {
            currentNode = currentNode->next;
        }
        retVal = tail->data;
        delete tail;
        currentNode->next = nullptr;
        tail = currentNode;
    }
    return retVal;
}

template <class T>
void List<T>::insert(const T& data, const size_t& position)
{
    if (position <= 0 || head == nullptr){
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
void List<T>::remove(const size_t& position)
{
    if (head == nullptr)
        return;
    if (position <= 0){
        Node *node = head->next;
        head->next = nullptr;
        delete head;
        head = node;
        return;
    }
    
    size_t index = 0;
    Node* currentNode = head;
    while (currentNode != nullptr)
    {
        if (index == position-1){
            Node* targetNode = currentNode->next;
            currentNode->next = targetNode->next;
            targetNode->next = nullptr;
            delete targetNode;
            break;
        }
        if (currentNode->next == tail){
            delete tail;
            currentNode->next = nullptr;
            tail = currentNode;
            break;
        }
        index++;
        currentNode = currentNode->next;
    }
}

template <typename T>
bool List<T>::isEmpty() const
{
    return head == nullptr;
}

template <class T>
T List<T>::at(const size_t& position) const
{
    if (head == nullptr)
        return T{};
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
T& List<T>::operator[](const size_t& index)
{
    if (index <= 0)
        return head->data;

    Node* currentNode = head->next;
    for(auto i = 1; i < index; ++i)
    {
        if (currentNode == nullptr)
            return tail->data;
        currentNode = currentNode->next;
    }
    return currentNode->data;
}

template <class T>
size_t List<T>::position(const T& data) const
{
    Node* currentNode = head;
    size_t index = 0;
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
size_t List<T>::recursive_search_helper(Node* currentNode, const T& key)
{
    if (currentNode == nullptr)
        return -1;
    if (currentNode->data == key)
        return 0;

    size_t position = recursive_search_helper(currentNode->next, key);
    if (position == -1)
        return -1;
    return position+1;
}

template <class T>
size_t List<T>::recursive_search(const T& data)
{
    return recursive_search_helper(head, data);
}

template <class T>
T List<T>::front() const
{
    return head != nullptr ? head->data : T{};
}

template <class T>
T List<T>::back() const
{
    return head != nullptr ? tail->data : T{};
}

template <typename T>
void List<T>::clear()
{
    if (head != nullptr){
        delete head;
        head = tail = nullptr;
    }
}

template <class T>
void List<T>::reverse()
{
    Node* currentNode = head;
    Node* prevNode = nullptr;
    
    while (currentNode != nullptr)
    {
        Node* nextInOriginalList = currentNode->next;
        currentNode->next = prevNode; 
        prevNode = currentNode;
        currentNode = nextInOriginalList;
    }

    tail = head;
    head = prevNode;
}

template <class T>
Vector<T> List<T>::to_vector() const
{
    Node* currentNode = head;
    Vector<T> list{};
    while (currentNode != nullptr)
    {
        list.push_back(currentNode->data);
        currentNode = currentNode->next;
    }
    
    return list;
}


#endif