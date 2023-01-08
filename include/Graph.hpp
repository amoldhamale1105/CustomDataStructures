#pragma once

#include <set>
#include <Hashmap.hpp>
#include <List.hpp>
#include <Queue.hpp>
#include <Pair.hpp>

template <typename T, class Hash = std::hash<T>, class KeyEqual = std::equal_to<T>>
class Graph
{
    class Node
    {
        T data;
        List<Pair<T,size_t>> neighbors;
    
    public:
        Node(const T& data) : data(data) {}
        friend class Graph<T,Hash,KeyEqual>;
    };

    Hashmap<T,Node*,Hash,KeyEqual> m_adjMap;
    void dfsHelper(const T& node, Vector<T>& dfsOut, Hashmap<T,bool,Hash,KeyEqual>& visitedMap) const;
    size_t findNeighbor(Node* adjNode, const T& node) const;
    bool traverse(const T& node, const T& dest, size_t& pathSum, const size_t& targetSum, Vector<T>& path, Hashmap<T,bool,Hash,KeyEqual>& visitedMap) const;

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
    size_t shortestPath(const T& source, const T& dest, Vector<T>& path) const;
    size_t shortestPath(const T& source, const T& dest) const;
    size_t weight(const T& fromNode, const T& toNode) const;
    List<T> neighbors(const T& node) const;
    Vector<T> nodes() const;
    size_t size() const;
    bool isEmpty() const;

    void operator=(const Graph<T,Hash,KeyEqual>& other);
};

/* Specializations defined for path computations */
template<typename T1, typename T2>
class std::greater<Pair<T1,T2>>
{
public:
    bool operator()(const Pair<T1,T2>& p1, const Pair<T1,T2>& p2) const
    {
        return p1.second > p2.second;      
    }
};

template<typename T1, typename T2>
class std::less<Pair<T1,T2>>
{
public:
    bool operator()(const Pair<T1,T2>& p1, const Pair<T1,T2>& p2) const
    {
        return p1.second < p2.second;      
    }
};

#define TEMPLATE_METHODS
#include "../src/Graph.cpp"
