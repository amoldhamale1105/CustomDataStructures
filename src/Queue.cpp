#ifndef TEMPLATE_METHODS
#include <Queue.hpp>

#else

template <class T>
Queue<T>::Queue(const size_t& size) : maxSize(size), currSize(0), frontIndex(0), rearIndex(size-1), head(nullptr), tail(nullptr)
{
    circularBuffer = new T[maxSize];
}

template <class T>
Queue<T>::Queue(Queue<T>& other) : head(nullptr), tail(nullptr), circularBuffer(nullptr)
{
    Vector<T> queueContainer;

    while (!other.isEmpty())
    {
        queueContainer.push_back(other.pop());
    }

    size_t n = queueContainer.size();
    for(auto i = 0; i < n; ++i)
    {
        T currentElement = queueContainer[i];
        this->push(currentElement);
        other.push(currentElement);
    }
}

template <class T>
Queue<T>::~Queue()
{
    if (head != nullptr)
        delete head;
    else if (circularBuffer != nullptr)
        delete [] circularBuffer;
}

template <class T>
void Queue<T>::push(const T& data)
{
    if (circularBuffer != nullptr){
        if (currSize == maxSize){
            std::cerr<<"Failed to push. Queue full!"<<std::endl;
            return;
        }
        rearIndex = (rearIndex+1) % maxSize;
        circularBuffer[rearIndex] = data;
        currSize++;
    }
    else{
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
}

template <class T>
T Queue<T>::pop()
{
    T retVal{};

    if (circularBuffer != nullptr){
        if (currSize > 0){
            retVal = circularBuffer[frontIndex];
            frontIndex = (frontIndex+1) % maxSize;
            currSize--;
        }
    }
    else{
        if (head != nullptr){
            Node *node = head->next;
            retVal = head->data;
            head->next = nullptr;
            delete head;
            head = node;
        }
    }

    return retVal;
}

template <class T>
T Queue<T>::front() const
{
    T retVal{};

    if (circularBuffer != nullptr){
        if (currSize > 0)
            retVal = circularBuffer[frontIndex];
    }
    else{
        if (head != nullptr)
            retVal = head->data;
    }

    return retVal;
}

template <class T>
T Queue<T>::rear() const
{
    T retVal{};

    if (circularBuffer != nullptr){
        if (currSize > 0)
            retVal = circularBuffer[rearIndex];
    }
    else{
        if (head != nullptr)
            retVal = tail->data;
    }
    
    return retVal;
}

template <class T>
size_t Queue<T>::size() const
{
    size_t size{0};

    if (circularBuffer != nullptr)
        size = currSize;
    else{
        Node* currentNode = head;
        while (currentNode != nullptr)
        {
            size++;
            currentNode = currentNode->next;
        }
    }
    
    return size;
}

template <class T>
void Queue<T>::clear()
{
    if (circularBuffer != nullptr){
        frontIndex = 0;
        rearIndex = maxSize-1;
        currSize = 0;
    }
    else{
        if (head != nullptr)
            delete head;
        head = nullptr;
    }
}

template <class T>
void Queue<T>::reverse()
{
    if (circularBuffer != nullptr){
        if (currSize > 0){
            size_t mid = currSize/2;
            mid = (frontIndex + mid) % maxSize;

            size_t i = 0;
            while (((i+frontIndex) % maxSize) < mid)
            {
                T temp = circularBuffer[(frontIndex+i)%maxSize];
                circularBuffer[(frontIndex+i)%maxSize] = circularBuffer[(frontIndex+currSize-i-1)%maxSize];
                circularBuffer[(frontIndex+currSize-i-1)%maxSize] = temp;
                i++;
            }
        }
    }
    else{
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
}

template <class T>
bool Queue<T>::isFull() const
{
    return circularBuffer != nullptr ? currSize == maxSize : false;
}

template <class T>
bool Queue<T>::isEmpty() const
{
    return circularBuffer != nullptr ? currSize == 0 : head == nullptr;
}

template <class T>
void Queue<T>::operator=(Queue<T>& other)
{
    head = tail = nullptr;
    Vector<T> queueContainer;

    while (!other.isEmpty())
    {
        queueContainer.push_back(other.pop());
    }

    size_t n = queueContainer.size();
    for(auto i = 0; i < n; ++i)
    {
        T currentElement = queueContainer[i];
        this->push(currentElement);
        other.push(currentElement);
    }
}

#endif