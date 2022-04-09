#pragma once

#include <iostream>
#include <cstring>
#include <utility>

template <typename T>
class Vector
{
    public:
        Vector();
        Vector(const int& initCapacity);
        Vector(const int& initCapacity, T&& fillData);
        ~Vector();

        void push_back(T&& data);
        T pop_back();
        bool isEmpty() const;
        T front() const;
        T back() const;
        T at(const int& index) const;
        int size() const;
        int capacity() const;

        T operator[](const int& index) const;

    private:
        T* arr;
        int currSize, maxSize;
};

#define TEMPLATE_METHODS
#include "../src/Vector.cpp"