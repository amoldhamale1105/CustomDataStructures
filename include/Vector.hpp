#include <iostream>
#include <cstring>

class Vector
{
    public:
        Vector();
        Vector(const int& initCapacity);
        Vector(const int& initCapacity, const int& fillData);
        ~Vector();

        void push_back(const int& data);
        int pop_back();
        bool isEmpty() const;
        int front() const;
        int back() const;
        int at(const int& index) const;
        int size() const;
        int capacity() const;

    private:
        int* arr;
        int currSize, maxSize;
};