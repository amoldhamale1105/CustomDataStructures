#pragma once

#include <iostream>
#include <cstring>
#include <utility>

template <typename T>
class Vector
{
    public:
        Vector();
        Vector(const size_t& initCapacity);
        Vector(const size_t& initCapacity, const T& fillData);
        Vector(const std::initializer_list<T>& initList);
        Vector(const Vector<T>& vec);
        virtual ~Vector();

        void push_back(const T& data);
        T pop_back();
        bool isEmpty() const;
        T front() const;
        T back() const;
        T at(const size_t& index) const;
        size_t size() const;
        size_t capacity() const;

        T& operator[](const size_t& index);
        void operator=(const Vector<T>& vec);

    private:
        T* arr;
        size_t currSize, maxSize;
};

#define TEMPLATE_METHODS
#include "../src/Vector.cpp"