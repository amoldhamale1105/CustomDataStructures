#include <Vector.hpp>

Vector::Vector() : currSize(0), maxSize(1)
{
    arr = new int[maxSize];
}

Vector::Vector(const int& initCapacity) : currSize(0), maxSize(initCapacity)
{
    arr = new int[maxSize];
}

Vector::Vector(const int& initCapacity, const int& fillData) : currSize(0), maxSize(initCapacity)
{
    arr = new int[maxSize];
    for (auto i = 0; i < maxSize; ++i)
    {
        arr[i] = fillData;
    }
    currSize = maxSize;
}

Vector::~Vector()
{
    delete [] arr;
}

void Vector::push_back(const int& data)
{
    if (currSize == maxSize){
        int* oldArr = arr;
        maxSize *= 2;
        arr = new int[maxSize];
        for (auto i = 0; i < maxSize; ++i)
        {
            arr[i] = oldArr[i];
        }

        delete [] oldArr;
        oldArr = nullptr;
    }

    arr[currSize] = data;
    currSize++;
}

int Vector::pop_back()
{
    int poppedData{-1};

    if (!isEmpty()){
        poppedData = arr[currSize-1];
        currSize--;
    }

    return poppedData;
}

bool Vector::isEmpty() const
{
    return currSize == 0;
}

int Vector::front() const
{
    return !isEmpty() ? arr[0] : -1;
}

int Vector::back() const
{
    return !isEmpty() ? arr[currSize-1] : -1;
}

int Vector::at(const int& index) const
{
    return !isEmpty() && index < currSize ? arr[index] : -1;
}

int Vector::size() const
{
    return currSize;
}

int Vector::capacity() const
{
    return maxSize;
}

