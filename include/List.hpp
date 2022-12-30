#pragma once

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
        size_t recursive_search_helper(Node*, const T&);
    
    public:
        List() : head(nullptr), tail(nullptr) {}
        List(const List<T>& other);
        virtual ~List();

        void operator=(const List<T>& other);
        T& operator[](const size_t& index);
        
        size_t size() const;
        void push_front(const T& data);
        void push_back(const T& data);
        T pop_front();
        T pop_back();
        void insert(const T& data, const size_t& position);
        void remove(const size_t& position);
        bool isEmpty() const;
        T at(const size_t& position) const;
        size_t position(const T& data) const;
        size_t recursive_search(const T& data);
        T front() const;
        T back() const;
        void reverse();
        Vector<T> to_vector() const;
};

#define TEMPLATE_METHODS
#include "../src/List.cpp"