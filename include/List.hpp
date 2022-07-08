#pragma once

#include <iostream>
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
        List(const List<T>& list) = delete;
        void operator=(const List<T>& list) = delete;
        void push_front(const T& data);
        void push_back(const T& data);
        void insert(const T& data, const int& position);
        T front() const;
        Vector<T> get_list() const;
};

#define TEMPLATE_METHODS
#include "../src/List.cpp"