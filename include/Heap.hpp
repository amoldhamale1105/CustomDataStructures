#pragma once

#include <Vector.hpp>

template <typename T>
class Heap
{
public:
    enum HeapType
    {
        MIN = 0, /* default */
        MAX
    };

    Heap(const HeapType& type = HeapType::MIN);
    Heap(const size_t& defSize, const HeapType& type = HeapType::MIN);
    virtual ~Heap();

    void push(const T& data);
    T pop();
    T top() const;
    size_t size() const;
    bool isEmpty() const;
    T& operator[](const size_t& index);

private:
    Vector<T> m_heapArr;
    HeapType m_type;
    void heapify(const size_t& index, const size_t& last);
    bool order(const T& parent, const T& child);
};

#define TEMPLATE_METHODS
#include "../src/Heap.cpp"