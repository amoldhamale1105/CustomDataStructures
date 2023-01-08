#ifndef TEMPLATE_METHODS
#include "Pair.hpp"

#else
template <typename T1, typename T2>
Pair<T1, T2>::Pair(const T1 &first, const T2 &second) : first(first), second(second)
{
}

template <typename T1, typename T2>
Pair<T1, T2>::~Pair()
{
}

template <typename T1, typename T2>
void Pair<T1, T2>::swap(Pair &other)
{
    T1 firstTemp = other.first;
    other.first = first;
    first = firstTemp;

    T2 secondTemp = other.second;
    other.second = second;
    second = secondTemp;
}

template <typename T1, typename T2>
bool Pair<T1, T2>::operator<(const Pair<T1, T2> &pair)
{
    return first < pair.first && second < pair.second;
}

template <typename T1, typename T2>
bool Pair<T1, T2>::operator>(const Pair<T1, T2> &pair)
{
    return first > pair.first && second > pair.second;
}

template <typename T1, typename T2>
bool Pair<T1, T2>::operator==(const Pair<T1, T2> &pair)
{
    return first == pair.first && second == pair.second;
}

template <typename T1, typename T2>
bool Pair<T1, T2>::operator!=(const Pair<T1, T2> &pair)
{
    return !(first == pair.first && second == pair.second);
}

template <typename T1, typename T2>
std::ostream &operator<<(std::ostream &stream, const Pair<T1, T2> &pair)
{
    stream << "{" << pair.first << "," << pair.second << "}";
    return stream;
}

#endif