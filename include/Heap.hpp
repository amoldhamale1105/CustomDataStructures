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
    T at(const size_t& index) const;

private:
    Vector<T> m_heapArr;
    void heapify(const size_t& index, const size_t& last);
};

#define TEMPLATE_METHODS
#include "../src/Heap.cpp"