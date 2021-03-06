#ifndef TEMPLATE_METHODS
#include <Vector.hpp>

#else

template <class T>
Vector<T>::Vector() : currSize(0), maxSize(1)
{
    arr = new T[maxSize];
}

template <class T>
Vector<T>::Vector(const int& initCapacity) : currSize(0), maxSize(initCapacity)
{
    arr = new T[maxSize];
}

template <class T>
Vector<T>::Vector(const int& initCapacity, const T& fillData) : currSize(0), maxSize(initCapacity)
{
    arr = new T[maxSize];
    for (auto i = 0; i < maxSize; ++i)
    {
        arr[i] = fillData;
    }
    currSize = maxSize;
}

template <class T>
Vector<T>::Vector(const Vector<T>& vec)
{
    currSize = vec.currSize;
    maxSize = vec.maxSize;
    arr = new T[maxSize];
    for (auto i = 0; i < maxSize; ++i)
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

template <class T>
bool Vector<T>::isEmpty() const
{
    return currSize == 0;
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
T Vector<T>::at(const int& index) const
{
    return !isEmpty() && index < currSize ? arr[index] : T{};
}

template <class T>
T& Vector<T>::operator[](const int& index)
{
    return !isEmpty() && index < currSize ? arr[index] : arr[0];
}

template <class T>
void Vector<T>::operator=(const Vector<T>& vec)
{
    currSize = vec.currSize;
    maxSize = vec.maxSize;
    arr = new T[maxSize];
    for (auto i = 0; i < maxSize; ++i)
    {
        arr[i] = vec.arr[i];
    }
}

template <class T>
int Vector<T>::size() const
{
    return currSize;
}

template <class T>
int Vector<T>::capacity() const
{
    return maxSize;
}

#endif