#pragma once
#include <string>
#include <memory>
#include <functional>
#include <Vector.hpp>

#define LOAD_LIMIT 2

template <typename Key, typename T, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>>
class Hashmap
{
    struct MapEntry
    {
        Key key;
        T value;
        MapEntry* next;

        MapEntry(const Key& key, const T& value) : key(key), value(value), next(nullptr) {}
        ~MapEntry() { if (next != nullptr) delete next; }
    };

    MapEntry** m_table;
    size_t m_currSize, m_tableSize;
    size_t getNewSize();
    void rehash();

public:
    Hashmap();
    Hashmap(const size_t& initSize);
    virtual ~Hashmap();

    void insert(const Key& key, const T& value);
    void erase(const Key& key);
    T at(const Key& key) const;
    bool contains(const Key& key) const;
    Key find(const T& value) const;
    Vector<Key> keys() const;
    bool isEmpty() const;
    void clear();
    
    T& operator[](const Key& key);
};

#define TEMPLATE_METHODS
#include "../src/Hashmap.cpp"