#pragma once

#include <ostream>

template <typename T1, typename T2>
class Pair
{
public:
    T1 first;
    T2 second;

    Pair() = default;
    Pair(const T1& first, const T2& second);
    virtual ~Pair();
    
    void swap(Pair& other);

    bool operator<(const Pair<T1,T2>& pair);
    bool operator>(const Pair<T1,T2>& pair);
    bool operator==(const Pair<T1,T2>& pair);
};

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& stream, const Pair<T1,T2>& pair);

#define TEMPLATE_METHODS
#include "../src/Pair.cpp"
