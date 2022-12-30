#ifndef TEMPLATE_METHODS
#include <Graph.hpp>

#else

template <typename T, class Hash, class KeyEqual>
Graph<T, Hash, KeyEqual>::Graph()
{
}

template <typename T, class Hash, class KeyEqual>
Graph<T, Hash, KeyEqual>::Graph(const Vector<T> &nodes)
{
    size_t index = nodes.size();
    while (index--)
    {
        T data = nodes.at(index);
        m_adjMap.insert(data, new Node(data));
    }
}

template <typename T, class Hash, class KeyEqual>
Graph<T, Hash, KeyEqual>::Graph(const Graph<T,Hash,KeyEqual> &other)
{
    Vector<T> keys = other.m_adjMap.keys();
    while (!keys.isEmpty())
    {
        T data = keys.pop_back();
        Node* adjNode = new Node(data);
        m_adjMap.insert(data, adjNode);
        adjNode->neighbors = other.m_adjMap.at(data)->neighbors;
    }
}

template <typename T, class Hash, class KeyEqual>
Graph<T, Hash, KeyEqual>::~Graph()
{
    Vector<T> keys = m_adjMap.keys();
    while (!keys.isEmpty())
    {
        Node* node = m_adjMap.at(keys.pop_back());
        if (node != nullptr)
            delete node;
    }
}

template <typename T, class Hash, class KeyEqual>
void Graph<T, Hash, KeyEqual>::insert(const T &node)
{
    m_adjMap.insert(node, new Node(node));
}

template <typename T, class Hash, class KeyEqual>
void Graph<T, Hash, KeyEqual>::addEdge(const T &firstNode, const T &secondNode, const bool &bidirectional)
{
    if (!m_adjMap.contains(firstNode))
        insert(firstNode);
    if (!m_adjMap.contains(secondNode))
        insert(secondNode);
    
    if (bidirectional)
        m_adjMap[secondNode]->neighbors.push_back(firstNode);
    m_adjMap[firstNode]->neighbors.push_back(secondNode);
}

template <typename T, class Hash, class KeyEqual>
void Graph<T, Hash, KeyEqual>::removeEdge(const T &firstNode, const T &secondNode, const bool& bothDirections)
{
    Node* adjNode;
    size_t pos;
    
    if (m_adjMap.contains(firstNode)){
        adjNode = m_adjMap.at(firstNode);
        if (adjNode != nullptr){
            pos = adjNode->neighbors.position(secondNode);
            if (pos != -1)
                adjNode->neighbors.remove(pos);
        }
    }

    if (bothDirections && m_adjMap.contains(secondNode)){
        adjNode = m_adjMap.at(secondNode);
        if (adjNode != nullptr){
            pos = adjNode->neighbors.position(firstNode);
            if (pos != -1)
                adjNode->neighbors.remove(pos);
        }
    }
}

template <typename T, class Hash, class KeyEqual>
void Graph<T, Hash, KeyEqual>::remove(const T &node)
{
    Node* adjNode = m_adjMap.at(node);

    while (!adjNode->neighbors.isEmpty())
    {
        removeEdge(node, adjNode->neighbors.front(), true);
    }
    m_adjMap.erase(node);
    if (adjNode != nullptr)
        delete adjNode;
    
    /* Remove node as a unidirectional neighbor of all other nodes */
    Vector<T> keys = m_adjMap.keys();
    while (!keys.isEmpty())
    {
        T data = keys.pop_back();
        removeEdge(data, node);
    }
}

template <typename T, class Hash, class KeyEqual>
bool Graph<T, Hash, KeyEqual>::connected(const T &firstNode, const T &secondNode) const
{
    return m_adjMap.contains(firstNode) && m_adjMap.at(firstNode)->neighbors.position(secondNode) != -1;
}

template <typename T, class Hash, class KeyEqual>
List<T> Graph<T, Hash, KeyEqual>::neighbors(const T &node) const
{
    return m_adjMap.contains(node) ? m_adjMap.at(node)->neighbors : List<T>();
}

template <typename T, class Hash, class KeyEqual>
Vector<T> Graph<T, Hash, KeyEqual>::nodes() const
{
    return m_adjMap.keys();
}

template <typename T, class Hash, class KeyEqual>
bool Graph<T, Hash, KeyEqual>::isEmpty() const
{
    return m_adjMap.isEmpty();
}

template <typename T, class Hash, class KeyEqual>
void Graph<T, Hash, KeyEqual>::operator=(const Graph<T,Hash,KeyEqual> &other)
{
    Vector<T> keys = other.m_adjMap.keys();
    while (!keys.isEmpty())
    {
        T data = keys.pop_back();
        Node* adjNode = new Node(data);
        m_adjMap.insert(data, adjNode);
        adjNode->neighbors = other.m_adjMap.at(data)->neighbors;
    }
}

#endif