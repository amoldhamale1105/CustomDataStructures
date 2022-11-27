#ifndef TEMPLATE_METHODS
#include "Hashmap.hpp"

#else
#include <iostream> // temp for debug logs. To be removed later
template <class Key, class T, class Allocator>
Hashmap<Key,T,Allocator>::Hashmap() : m_currSize(0), m_tableSize(11)
{
    m_table = Allocator{}.allocate(m_tableSize);
}

template <class Key, class T, class Allocator>
Hashmap<Key,T,Allocator>::Hashmap(const size_t& initSize) : m_currSize(0), m_tableSize(initSize)
{
    Allocator alloc;
    m_table = alloc.allocate(m_tableSize);
    alloc.construct(m_table+2, "hello", 6); //Sample construction of second map table entry
}


template <class Key, class T, class Allocator>
Hashmap<Key,T,Allocator>::~Hashmap()
{
    std::cout<<"verifying table entry before dealloc "<<m_table[2].key<<" "<<m_table[2].value<<std::endl;
    Allocator{}.deallocate(m_table, m_tableSize);
}

#endif