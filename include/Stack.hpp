#pragma once
#include <iostream>

template <typename T>
class Stack
{
    class Node
    {
        T data;
        Node* next;

        public:
            Node(const T& data) : data(data), next(nullptr) {}
            ~Node() { if (next != nullptr) delete next; }
        
        friend class Stack<T>;
    };

    Node* head;

    public:
        Stack() : head(nullptr) {}
        ~Stack() { if (head != nullptr) delete head; }
        void push(const T& data);
        T pop();
        T top() const;
        void clear();
};

#define TEMPLATE_METHODS
#include "../src/Stack.cpp"