#ifndef TEMPLATE_METHODS
#include "Heap.hpp"

#else

template <class T, class Compare>
Heap<T,Compare>::Heap()
{
    m_heapArr.push_back(T());
}

template <class T, class Compare>
Heap<T,Compare>::Heap(const size_t& defSize)
{
    Vector<T> heapArr(defSize);
    heapArr.push_back(T());
    m_heapArr = heapArr;
}

template <class T, class Compare>
Heap<T,Compare>::~Heap()
{
}

template <class T, class Compare>
size_t Heap<T,Compare>::size() const
{
    return m_heapArr.size() - 1;
}

template <class T, class Compare>
void Heap<T,Compare>::push(const T& data)
{
    m_heapArr.push_back(data);
    size_t currIndex = m_heapArr.size() - 1;
    size_t parent = currIndex/2;

    while (currIndex > 1 && !order(m_heapArr[parent], m_heapArr[currIndex]))
    {
        std::swap(m_heapArr[currIndex], m_heapArr[parent]);
        currIndex = parent;
        parent /= 2;        
    }
}

template <class T, class Compare>
T Heap<T,Compare>::top() const
{
    return m_heapArr.size() > 1 ? m_heapArr.at(1) : m_heapArr.at(0);
}

template <class T, class Compare>
T Heap<T,Compare>::pop()
{
    T retVal{};
    
    if (m_heapArr.size() > 1){
        size_t topIndex = 1;
        size_t lastIndex = m_heapArr.size() - 1;

        std::swap(m_heapArr[topIndex], m_heapArr[lastIndex]);
        retVal = m_heapArr.pop_back();
        lastIndex--;

        heapify(topIndex, lastIndex);
    }
    
    return retVal;
}

template <class T, class Compare>
void Heap<T,Compare>::heapify(const size_t& index, const size_t& last)
{
    size_t leftChild = 2*index;
    size_t rightChild = 2*index + 1;
    size_t topIndex = index;

    if (leftChild < last && !order(m_heapArr[index], m_heapArr[leftChild]))
        topIndex = leftChild;
    if (rightChild < last && !order(m_heapArr[topIndex], m_heapArr[rightChild]))
        topIndex = rightChild;

    if (topIndex != index){
        std::swap(m_heapArr[topIndex], m_heapArr[index]);
        heapify(topIndex, last);
    }
}

template <class T, class Compare>
bool Heap<T,Compare>::isEmpty() const
{
    return m_heapArr.size() <= 1;
}

template <typename T, typename Compare>
T Heap<T, Compare>::at(const size_t &index) const
{
    return index < m_heapArr.size()-1 ? m_heapArr.at(index+1) : T{};
}

template <class T, class Compare>
bool Heap<T,Compare>::order(const T& parent, const T& child)
{
    return Compare{}(parent, child);
}

#endif