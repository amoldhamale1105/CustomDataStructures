#pragma once
#include <string>
#include <memory>
#include <functional>
#include <Vector.hpp>

/* Load factor of the hashtable as ratio of current size and table size, used to rehash the table with new size */
#define LOAD_LIMIT 1
#define DEFAULT_SIZE 11 /* This must be prime number */

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
    Hashmap(const Hashmap<Key,T,Hash,KeyEqual>& other);
    virtual ~Hashmap();

    void insert(const Key& key, const T& value);
    void erase(const Key& key);
    T at(const Key& key) const;
    bool contains(const Key& key) const;
    Key find(const T& value) const;
    size_t size() const;
    Vector<Key> keys() const;
    bool isEmpty() const;
    void clear();
    
    T& operator[](const Key& key);
    void operator=(const Hashmap<Key,T,Hash,KeyEqual>& other);
};

#define TEMPLATE_METHODS
#include "../src/Hashmap.cpp"