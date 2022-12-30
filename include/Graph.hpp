#pragma once

#include <Hashmap.hpp>
#include <List.hpp>

template <typename T, class Hash = std::hash<T>, class KeyEqual = std::equal_to<T>>
class Graph
{
    class Node
    {
        T data;
        List<T> neighbors;
    
    public:
        Node(const T& data) : data(data) {}
        friend class Graph<T,Hash,KeyEqual>;
    };

    Hashmap<T,Node*,Hash,KeyEqual> m_adjMap;

public:
    Graph();
    Graph(const Vector<T>& nodes);
    Graph(const Graph<T,Hash,KeyEqual>& other);
    virtual ~Graph();

    void insert(const T& node);
    void addEdge(const T& firstNode, const T& secondNode, const bool& bidirectional = false);
    void removeEdge(const T& firstNode, const T& secondNode, const bool& bothDirections = false);
    void remove(const T& node);
    bool connected(const T& firstNode, const T& secondNode) const;
    List<T> neighbors(const T& node) const;
    Vector<T> nodes() const;
    bool isEmpty() const;

    void operator=(const Graph<T,Hash,KeyEqual>& other);
};

#define TEMPLATE_METHODS
#include "../src/Graph.cpp"
