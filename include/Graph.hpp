#pragma once

#include <Hashmap.hpp>
#include <List.hpp>
#include <Queue.hpp>

template <typename T, class Hash = std::hash<T>, class KeyEqual = std::equal_to<T>>
class Graph
{
    class Node
    {
        T data;
        List<T> neighbors;
        Hashmap<T,size_t> weights;
    
    public:
        Node(const T& data) : data(data) {}
        friend class Graph<T,Hash,KeyEqual>;
    };

    Hashmap<T,Node*,Hash,KeyEqual> m_adjMap;
    void dfsHelper(const T& node, Vector<T>& dfsOut, Hashmap<T,bool>& visitedMap) const;

public:
    Graph();
    Graph(const Vector<T>& nodes);
    Graph(const Graph<T,Hash,KeyEqual>& other);
    virtual ~Graph();

    void insert(const T& node);
    void addEdge(const T& firstNode, const T& secondNode, const bool& bidirectional = false, const size_t& weight = SIZE_MAX);
    void removeEdge(const T& firstNode, const T& secondNode, const bool& bothDirections = false);
    void remove(const T& node);
    bool connected(const T& firstNode, const T& secondNode) const;
    Vector<T> bfs(const T& startNode) const;
    Vector<T> dfs(const T& startNode) const;
    Vector<T> topologicalSort() const;
    List<T> neighbors(const T& node) const;
    Vector<T> nodes() const;
    size_t size() const;
    bool isEmpty() const;

    void operator=(const Graph<T,Hash,KeyEqual>& other);
};

#define TEMPLATE_METHODS
#include "../src/Graph.cpp"
