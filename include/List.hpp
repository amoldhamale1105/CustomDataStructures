#pragma once

#include <iostream>
#include <utility>
#include <Vector.hpp>

template<typename T>
class List
{
        class Node
        {
                T data{};
                Node* next;
            
            public:
                Node(const T& data) : data(data), next(nullptr) {}
            friend class List<T>;
        };
        Node* head;
        Node* tail;
    
    public:
        List() : head(nullptr), tail(nullptr) {}
        template <class U>
        void push_front(U&& data);
        template <class U>
        void push_back(U&& data);
        T front() const;
        Vector<T> get_list() const;
};

#define TEMPLATE_METHODS
#include "../src/List.cpp"