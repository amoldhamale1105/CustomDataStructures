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
        void push_front(const T& data);
        void push_back(const T& data);
        T pop_front();
        T pop_back();
        void insert(const T& data, const int& position);
        void remove(const int& position);
        T find(const int& position) const;
        int position(const T& data) const;
        int recursive_search(const T& data);
        T front() const;
        Vector<T> get_list() const;
};

#define TEMPLATE_METHODS
#include "../src/List.cpp"