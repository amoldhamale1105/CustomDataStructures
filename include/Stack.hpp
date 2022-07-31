#pragma once
#include <iostream>
#include <Vector.hpp>

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
    void insertAtBottom(const T& data);

    public:
        Stack() : head(nullptr) {}
        Stack(Stack<T>& other);
        ~Stack() { if (head != nullptr) delete head; }
        void push(const T& data);
        T pop();
        T top() const;
        int depth() const;
        void clear();
        bool isEmpty() const;
        void reverse();

        void operator=(Stack<T>& other);
};

#define TEMPLATE_METHODS
#include "../src/Stack.cpp"