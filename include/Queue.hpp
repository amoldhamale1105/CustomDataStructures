#pragma once
#include <iostream>
#include <Vector.hpp>

template <typename T>
class Queue
{
    class Node
    {
        T data;
        Node* next;

        public:
            Node(const T& data) : data(data), next(nullptr) {}
            ~Node() { if (next != nullptr) delete next; }
        
        friend class Queue<T>;
    };

    Node* head;
    Node* tail;
    T* circularBuffer;
    size_t currSize, maxSize, frontIndex, rearIndex;

    public:
        Queue() : head(nullptr), tail(nullptr), circularBuffer(nullptr) {}
        Queue(const size_t& size);
        Queue(const Queue<T>& other);
        virtual ~Queue();
        void push(const T& data);
        T pop();
        T front() const;
        T rear() const;
        size_t size() const;
        void clear();
        bool isFull() const;
        bool isEmpty() const;
        void reverse();

        void operator=(const Queue<T>& other);
};

#define TEMPLATE_METHODS
#include "../src/Queue.cpp"