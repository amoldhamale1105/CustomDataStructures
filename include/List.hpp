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
                ~Node() { if (next != nullptr) delete next; }
            friend class List<T>;
        };
        Node* head;
        Node* tail;
        int recursive_search_helper(Node*, const T&);
    
    public:
        List() : head(nullptr), tail(nullptr) {}
        List(const List<T>& list) = delete;
        ~List();

        void operator=(const List<T>& list) = delete;
        T& operator[](const int& index);
        
        int size() const;
        void push_front(const T& data);
        void push_back(const T& data);
        T pop_front();
        T pop_back();
        void insert(const T& data, const int& position);
        void remove(const int& position);
        T at(const int& position) const;
        int position(const T& data) const;
        int recursive_search(const T& data);
        T front() const;
        T back() const;
        void reverse();
        Vector<T> to_vector() const;
};

#define TEMPLATE_METHODS
#include "../src/List.cpp"