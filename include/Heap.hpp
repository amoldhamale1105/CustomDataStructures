#pragma once

#include <Vector.hpp>

template<typename T>
class Heap
{
public:
    Heap();
    Heap(const size_t& defSize);
    virtual ~Heap();

    size_t size() const;
    void push(const T& data);
    void pop();
    T top() const;
    bool isEmpty() const;
    T& operator[](const size_t& index);

private:
    Vector<T> m_heapArr;
    void heapify(const size_t& index, const size_t& last);
    bool compare(const T& e1, const T& e2);
};

#define TEMPLATE_METHODS
#include "../src/Heap.cpp"