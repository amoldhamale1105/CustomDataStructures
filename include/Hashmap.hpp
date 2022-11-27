#pragma once
#include <string>
#include <memory>

template <typename Key, typename T>
struct MapEntry
{
    Key key;
    T value;
    MapEntry* next;

    MapEntry(const Key& key, const T& value) : key(key), value(value), next(nullptr) {}
    ~MapEntry() { if (next != nullptr) delete next; }
};

template <typename Key, typename T, class Allocator = std::allocator<MapEntry<Key,T>>>
class Hashmap
{
    MapEntry<Key,T>* m_table;
    size_t m_currSize, m_tableSize;

public:
    Hashmap();
    Hashmap(const size_t& initSize);
    virtual ~Hashmap();
};

#define TEMPLATE_METHODS
#include "../src/Hashmap.cpp"