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
template <class U>
Vector<T>::Vector(const int& initCapacity, U&& fillData) : currSize(0), maxSize(initCapacity)
{
    arr = new T[maxSize];
    for (auto i = 0; i < maxSize; ++i)
    {
        arr[i] = std::forward<U>(fillData);
    }
    currSize = maxSize;
}

template <class T>
Vector<T>::~Vector()
{
    delete [] arr;
}

template <class T>
template <class U>
void Vector<T>::push_back(U&& data)
{
    if (currSize == maxSize){
        T* oldArr = arr;
        maxSize *= 2;
        arr = new T[maxSize];
        for (auto i = 0; i < maxSize; ++i)
        {
            arr[i] = oldArr[i];
        }

        delete [] oldArr;
        oldArr = nullptr;
    }

    arr[currSize] = std::forward<U>(data);
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
T Vector<T>::operator[](const int& index) const
{
    return at(index);
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