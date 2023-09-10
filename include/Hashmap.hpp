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

/* Hashmap Impl */

template <class Key, class T, class Hash, class KeyEqual>
Hashmap<Key,T,Hash,KeyEqual>::Hashmap() : m_currSize(0), m_tableSize(DEFAULT_SIZE)
{
    m_table = new MapEntry*[m_tableSize];
    for(size_t i = 0; i < m_tableSize; i++)
    {
        m_table[i] = nullptr;
    }
}

template <class Key, class T, class Hash, class KeyEqual>
Hashmap<Key,T,Hash,KeyEqual>::Hashmap(const size_t& initSize) : m_currSize(0), m_tableSize(initSize)
{
    m_table = new MapEntry*[m_tableSize];
    for(size_t i = 0; i < m_tableSize; i++)
    {
        m_table[i] = nullptr;
    }
}

template <class Key, class T, class Hash, class KeyEqual>
Hashmap<Key,T,Hash,KeyEqual>::Hashmap(const Hashmap<Key,T,Hash,KeyEqual>& other) : m_currSize(0), m_tableSize(other.m_tableSize)
{
    m_table = new MapEntry*[m_tableSize];
    for(size_t i = 0; i < m_tableSize; i++)
    {
        m_table[i] = nullptr;
    }

    for(auto i = 0; i < other.m_tableSize; i++)
    {
        MapEntry* entry = other.m_table[i];
        while (entry != nullptr)
        {
            insert(entry->key, entry->value);
            entry = entry->next;
        }
    }
}

template <class Key, class T, class Hash, class KeyEqual>
Hashmap<Key,T,Hash,KeyEqual>::~Hashmap()
{
    for(size_t i = 0; i < m_tableSize; i++)
    {
        if (m_table[i] != nullptr)
            delete m_table[i];
    }
    delete [] m_table;
}

template <class Key, class T, class Hash, class KeyEqual>
size_t Hashmap<Key,T,Hash,KeyEqual>::getNewSize()
{
    bool nextPrimeFound{false};
    size_t newSize{m_tableSize*2-1};

    for(auto i = m_tableSize*2-1; i > m_tableSize; i-=2)
    {
        nextPrimeFound = true;
        for(auto j = 3; j*j <= i; j+=2)
        {
            if (i%j == 0){
                nextPrimeFound = false;
                break;
            }
        }

        if (nextPrimeFound){
            newSize = i;
            break;
        }
    }

    return newSize;
}

template <class Key, class T, class Hash, class KeyEqual>
void Hashmap<Key,T,Hash,KeyEqual>::rehash()
{
    MapEntry** oldTable = m_table;
    size_t oldSize = m_tableSize;

    m_tableSize = getNewSize();
    m_table = new MapEntry*[m_tableSize];
    m_currSize = 0;

    for(auto i = 0; i < m_tableSize; i++)
    {
        m_table[i] = nullptr;
    }

    for(auto i = 0; i < oldSize; i++)
    {
        MapEntry* entry = oldTable[i];
        while (entry != nullptr)
        {
            insert(entry->key, entry->value);
            entry = entry->next;
        }

        if (oldTable[i] != nullptr)
            delete oldTable[i];
    }

    delete [] oldTable;
}

template <class Key, class T, class Hash, class KeyEqual>
void Hashmap<Key,T,Hash,KeyEqual>::insert(const Key& key, const T& value)
{
    size_t targetIndex = Hash{}(key) % m_tableSize;
    MapEntry* entry = m_table[targetIndex];
    KeyEqual compKey;
    
    while (entry != nullptr)
    {
        if (compKey(key, entry->key)){
            entry->value = value;
            return;
        }
        entry = entry->next;
    }
    
    float load = static_cast<float>(m_currSize+1)/static_cast<float>(m_tableSize);
    if (load > LOAD_LIMIT)
        rehash();

    targetIndex = Hash{}(key) % m_tableSize;
    entry = new MapEntry(key, value);
    entry->next = m_table[targetIndex];
    m_table[targetIndex] = entry;
    m_currSize++;
}

template <class Key, class T, class Hash, class KeyEqual>
T Hashmap<Key,T,Hash,KeyEqual>::at(const Key& key) const
{
    T retVal{};
    size_t targetIndex = Hash{}(key) % m_tableSize;
    MapEntry* entry = m_table[targetIndex];
    KeyEqual compKey;
    
    while (entry != nullptr)
    {
        if (compKey(key, entry->key)){
            retVal = entry->value;
            break;
        }
        entry = entry->next;
    }
    
    return retVal;
}

template <class Key, class T, class Hash, class KeyEqual>
T& Hashmap<Key,T,Hash,KeyEqual>::operator[](const Key& key)
{
    size_t targetIndex = Hash{}(key) % m_tableSize;
    MapEntry* entry = m_table[targetIndex];
    KeyEqual compKey;
    
    while (entry != nullptr)
    {
        if (compKey(key, entry->key))
            return entry->value;
        
        entry = entry->next;
    }

    /* Create a new entry if it does not exist */
    insert(key, T{});
    return (*this)[key];
}

template <class Key, class T, class Hash, class KeyEqual>
void Hashmap<Key,T,Hash,KeyEqual>::operator=(const Hashmap<Key,T,Hash,KeyEqual>& other)
{
    clear();

    for(auto i = 0; i < other.m_tableSize; i++)
    {
        MapEntry* entry = other.m_table[i];
        while (entry != nullptr)
        {
            insert(entry->key, entry->value);
            entry = entry->next;
        }
    }
}

template <class Key, class T, class Hash, class KeyEqual>
bool Hashmap<Key,T,Hash,KeyEqual>::isEmpty() const
{
    bool empty{true};

    for(auto i = 0; i < m_tableSize; i++)
    {
        if (m_table[i] != nullptr){
            empty = false;
            break;
        }
    }

    return empty;
}

template <class Key, class T, class Hash, class KeyEqual>
Vector<Key> Hashmap<Key,T,Hash,KeyEqual>::keys() const
{
    Vector<Key> keyCont;
    
    for(auto i = 0; i < m_tableSize; i++)
    {
        MapEntry* entry = m_table[i];
        while (entry != nullptr)
        {
            keyCont.push_back(entry->key);
            entry = entry->next;
        }
    }

    return keyCont;
}

template <class Key, class T, class Hash, class KeyEqual>
Key Hashmap<Key,T,Hash,KeyEqual>::find(const T& value) const
{
    Key firstMatch{};

    for(auto i = 0; i < m_tableSize; i++)
    {
        MapEntry* entry = m_table[i];
        while (entry != nullptr)
        {
            if (value == entry->value){
                firstMatch = entry->key;
                break;
            }
            entry = entry->next;
        }
    }

    return firstMatch;
}

template <class Key, class T, class Hash, class KeyEqual>
size_t Hashmap<Key,T,Hash,KeyEqual>::size() const
{
    return m_currSize;
}

template <class Key, class T, class Hash, class KeyEqual>
bool Hashmap<Key,T,Hash,KeyEqual>::contains(const Key& key) const
{
    size_t targetIndex = Hash{}(key) % m_tableSize;
    MapEntry* entry = m_table[targetIndex];
    KeyEqual compKey;
    bool keyPresent{false};

    while (entry != nullptr)
    {
        if (compKey(key, entry->key)){
            keyPresent = true;
            break;
        }
        entry = entry->next;
    }

    return keyPresent;
}

template <class Key, class T, class Hash, class KeyEqual>
void Hashmap<Key,T,Hash,KeyEqual>::erase(const Key& key)
{
    size_t targetIndex = Hash{}(key) % m_tableSize;
    MapEntry* entry = m_table[targetIndex];
    MapEntry* prevEntry = nullptr;
    KeyEqual compKey;

    if (entry != nullptr){
        if (compKey(key, entry->key)){
            m_table[targetIndex] = entry->next;
            entry->next = nullptr;
            delete entry;
            m_currSize--;
            return;
        }
        prevEntry = entry;
        entry = entry->next;
    }
    
    while (entry != nullptr)
    {
        if (compKey(key, entry->key)){
            prevEntry->next = entry->next;
            entry->next = nullptr;
            delete entry;
            m_currSize--;
            break;
        }
        prevEntry = entry;
        entry = entry->next;
    }
}

template <class Key, class T, class Hash, class KeyEqual>
void Hashmap<Key,T,Hash,KeyEqual>::clear()
{
    for(auto i = 0; i < m_tableSize; i++)
    {
        MapEntry* entry = m_table[i];
        if (entry != nullptr){
            delete entry;
            m_table[i] = nullptr;
        }
    }
    m_currSize = 0;
}
