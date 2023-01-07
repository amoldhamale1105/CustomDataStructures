#pragma once

#include <Vector.hpp>

template <typename T, typename Compare = std::less<T>>
class Heap
{
public:
    Heap();
    Heap(const size_t& defSize);
    virtual ~Heap();

    void push(const T& data);
    T pop();
    T top() const;
    size_t size() const;
    bool isEmpty() const;
    size_t position(const T& data) const;
    T& operator[](const size_t& index);

private:
    Vector<T> m_heapArr;
    void heapify(const size_t& index, const size_t& last);
    bool order(const T& parent, const T& child);
};

#define TEMPLATE_METHODS
#include "../src/Heap.cpp"