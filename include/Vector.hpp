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
    void clear();
    bool isEmpty() const;
    bool contains(const T& data) const;
    T front() const;
    T back() const;
    T at(const size_t& index) const;
    size_t position(const T& data) const;
    size_t size() const;
    size_t capacity() const;

    T& operator[](const size_t& index);
    void operator=(const Vector<T>& vec);

private:
    T* arr;
    size_t currSize, maxSize;
};

/* Vector Impl */

template <class T>
Vector<T>::Vector() : currSize(0), maxSize(1)
{
    arr = new T[maxSize];
}

template <class T>
Vector<T>::Vector(const size_t& initCapacity) : currSize(0), maxSize(initCapacity)
{
    arr = new T[maxSize];
}

template <class T>
Vector<T>::Vector(const size_t& initCapacity, const T& fillData) : currSize(0), maxSize(initCapacity)
{
    arr = new T[maxSize];
    for (auto i = 0; i < maxSize; ++i)
    {
        arr[i] = fillData;
    }
    currSize = maxSize;
}

template <typename T>
Vector<T>::Vector(const std::initializer_list<T> &initList) : currSize(0), maxSize(initList.size())
{
    arr = new T[maxSize];
    for (auto i = 0; i < maxSize; ++i)
    {
        arr[i] = *(initList.begin()+i);
    }
    currSize = maxSize;
}

template <class T>
Vector<T>::Vector(const Vector<T>& vec) : currSize(vec.currSize), maxSize(vec.maxSize)
{
    arr = new T[maxSize];
    for (auto i = 0; i < currSize; i++)
    {
        arr[i] = vec.arr[i];
    }
}

template <class T>
Vector<T>::~Vector()
{
    delete [] arr;
}

template <class T>
void Vector<T>::push_back(const T& data)
{
    if (currSize == maxSize){
        T* oldArr = arr;
        maxSize *= 2;
        arr = new T[maxSize];
        for (auto i = 0; i < maxSize/2; ++i)
        {
            arr[i] = oldArr[i];
        }

        delete [] oldArr;
        oldArr = nullptr;
    }

    arr[currSize] = data;
    currSize++;
}

template <class T>
T Vector<T>::pop_back()
{
    T poppedData{};

    if (!isEmpty()){
        poppedData = arr[currSize-1];
        currSize--;
    }

    return poppedData;
}

template <typename T>
void Vector<T>::clear()
{
    currSize = 0;
}

template <class T>
bool Vector<T>::isEmpty() const
{
    return currSize == 0;
}

template <typename T>
bool Vector<T>::contains(const T &data) const
{
    bool dataPresent{false};

    for(auto i = 0; i < currSize; i++)
    {
        if (data == arr[i]){
            dataPresent = true;
            break;
        }
    }
    return dataPresent;
}

template <class T>
T Vector<T>::front() const
{
    return !isEmpty() ? arr[0] : T{};
}

template <class T>
T Vector<T>::back() const
{
    return !isEmpty() ? arr[currSize-1] : T{};
}

template <class T>
T Vector<T>::at(const size_t& index) const
{
    return !isEmpty() && index < currSize ? arr[index] : T{};
}

template <typename T>
size_t Vector<T>::position(const T &data) const
{
    size_t dataIndex = -1;

    for(auto i = 0; i < currSize; i++)
    {
        if (data == arr[i]){
            dataIndex = i;
            break;
        }
    }
    return dataIndex;
}

template <class T>
T& Vector<T>::operator[](const size_t& index)
{
    return !isEmpty() && index < currSize ? arr[index] : arr[0];
}

template <class T>
void Vector<T>::operator=(const Vector<T>& vec)
{
    if (maxSize < vec.currSize){
        delete [] arr;
        maxSize = vec.maxSize;
        arr = new T[maxSize];
    }
    currSize = vec.currSize;

    for (auto i = 0; i < currSize; i++)
    {
        arr[i] = vec.arr[i];
    }
}

template <class T>
size_t Vector<T>::size() const
{
    return currSize;
}

template <class T>
size_t Vector<T>::capacity() const
{
    return maxSize;
}
