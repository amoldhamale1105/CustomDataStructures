#ifndef TEMPLATE_METHODS
#include "Heap.hpp"

#else

template<typename T>
Heap<T>::Heap()
{
    m_heapArr.push_back(T());
}

template<typename T>
Heap<T>::Heap(const size_t& defSize)
{
    Vector<T> heapArr(defSize);
    heapArr.push_back(T());
    m_heapArr = heapArr;
}

template<class T>
Heap<T>::~Heap()
{
}

template <class T>
size_t Heap<T>::size() const
{
    return m_heapArr.size() - 1;
}

template<class T>
void Heap<T>::push(const T& data)
{
    m_heapArr.push_back(data);
    size_t currIndex = m_heapArr.size() - 1;
    size_t parent = currIndex/2;

    // Current config is min heap tree
    while (currIndex > 1 && m_heapArr[parent] > m_heapArr[currIndex])
    {
        std::swap(m_heapArr[currIndex], m_heapArr[parent]);
        currIndex = parent;
        parent /= 2;        
    }
}

template <class T>
T Heap<T>::top() const
{
    return m_heapArr.size() > 1 ? m_heapArr.at(1) : m_heapArr.at(0);
}

template <class T>
void Heap<T>::pop()
{
    if (m_heapArr.size() <= 1)
        return;

    size_t currIndex = 1;
    size_t lastIndex = m_heapArr.size() - 1;

    std::swap(m_heapArr[1], m_heapArr[lastIndex]);
    m_heapArr.pop_back();
    lastIndex--;

    heapify(currIndex, lastIndex);
}

template <class T>
void Heap<T>::heapify(const size_t& index, const size_t& last)
{
    size_t leftChild = 2*index;
    size_t rightChild = 2*index + 1;
    size_t minIndex = index;

    if (leftChild < last && m_heapArr[leftChild] < m_heapArr[index])
        minIndex = leftChild;
    if (rightChild < last && m_heapArr[rightChild] < m_heapArr[minIndex])
        minIndex = rightChild;

    if (minIndex != index){
        std::swap(m_heapArr[minIndex], m_heapArr[index]);
        heapify(minIndex, last);
    }
}

template <class T>
bool Heap<T>::isEmpty() const
{
    return m_heapArr.size() <= 1;
}

template <class T>
bool Heap<T>::compare(const T&, const T&)
{
    return false;
}

template<class T>
T& Heap<T>::operator[](const size_t& index)
{
    size_t maxSize = m_heapArr.size();
    return index >= maxSize-1 ? m_heapArr[maxSize-1] : m_heapArr[index+1];
}

#endif