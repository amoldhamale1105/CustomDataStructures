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
void Graph<T, Hash, KeyEqual>::addEdge(const T &firstNode, const T &secondNode, const bool &bidirectional, const size_t& weight)
{
    if (!m_adjMap.contains(firstNode))
        insert(firstNode);
    if (!m_adjMap.contains(secondNode))
        insert(secondNode);
    
    Node* adjNode;
    size_t pos;

    if (bidirectional){
        adjNode = m_adjMap.at(secondNode);
        pos = adjNode->neighbors.position(firstNode);
        if (pos == -1){
            adjNode->neighbors.push_back(firstNode);
            adjNode->weights.push_back(weight);
        }
        else
            adjNode->weights[pos] = weight;
    }
    
    adjNode = m_adjMap.at(firstNode);
    pos = adjNode->neighbors.position(secondNode);
    if (pos == -1){
        adjNode->neighbors.push_back(secondNode);
        adjNode->weights.push_back(weight);
    }
    else
        adjNode->weights[pos] = weight;
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
            if (pos != -1){
                adjNode->neighbors.remove(pos);
                adjNode->weights.remove(pos);
            }
        }
    }

    if (bothDirections && m_adjMap.contains(secondNode)){
        adjNode = m_adjMap.at(secondNode);
        if (adjNode != nullptr){
            pos = adjNode->neighbors.position(firstNode);
            if (pos != -1){
                adjNode->neighbors.remove(pos);
                adjNode->weights.remove(pos);
            }
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
Vector<T> Graph<T, Hash, KeyEqual>::bfs(const T &startNode) const
{
    if (!m_adjMap.contains(startNode))
        return {};
    
    Hashmap<T,bool> visitedMap;
    Queue<T> nodeQue;
    Vector<T> bfsOut;

    nodeQue.push(startNode);
    visitedMap.insert(startNode, true);

    while (!nodeQue.isEmpty())
    {
        T node = nodeQue.pop();
        bfsOut.push_back(node);

        Node* adjNode = m_adjMap.at(node);
        size_t neighborCount = adjNode->neighbors.size();
        for(auto i = 0; i < neighborCount; i++)
        {
            T neighbor = adjNode->neighbors.at(i);
            if (!visitedMap.contains(neighbor)){
                nodeQue.push(neighbor);
                visitedMap.insert(neighbor, true);
            }
        }
    }
    
    return bfsOut;
}

template <typename T, class Hash, class KeyEqual>
void Graph<T, Hash, KeyEqual>::dfsHelper(const T &node, Vector<T>& dfsOut, Hashmap<T, bool> &visitedMap) const
{
    visitedMap.insert(node, true);
    dfsOut.push_back(node);

    Node* adjNode = m_adjMap.at(node);
    size_t neighborCount = adjNode->neighbors.size();
    for(auto i = 0; i < neighborCount; i++)
    {
        T neighbor = adjNode->neighbors.at(i);
        if (!visitedMap.contains(neighbor))
            dfsHelper(neighbor, dfsOut, visitedMap);
    }
}

template <typename T, class Hash, class KeyEqual>
Vector<T> Graph<T, Hash, KeyEqual>::dfs(const T &startNode) const
{
    if (!m_adjMap.contains(startNode))
        return {};
    
    Hashmap<T,bool> visitedMap;
    Vector<T> dfsOut;
    dfsHelper(startNode, dfsOut, visitedMap);
    
    return dfsOut;
}

template <typename T, class Hash, class KeyEqual>
Vector<T> Graph<T, Hash, KeyEqual>::topologicalSort() const
{
    Hashmap<T,int> indegreeMap;
    Queue<T> readyQue;
    Vector<T> sortedOut;
    Vector<T> nodes = m_adjMap.keys();
    size_t total = m_adjMap.size();

    /* Create an indegree map for all nodes prior to sorting */
    for(auto i = 0; i < total; i++)
    {
        T node = nodes.at(i);
        if (!indegreeMap.contains(node))
            indegreeMap.insert(node, 0);
        Node* adjNode = m_adjMap.at(node);
        size_t neighborCount = adjNode->neighbors.size();
        for(auto i = 0; i < neighborCount; i++)
        {
            indegreeMap[adjNode->neighbors.at(i)]++;
        }
    }

    /* Enqueue indegree nodes with 0 count */
    for(auto i = 0; i < total; i++)
    {
        T node = nodes.at(i);
        if (indegreeMap.at(node) == 0)
            readyQue.push(node);
    }

    /* Process ready queue */
    while (!readyQue.isEmpty())
    {
        T readyNode = readyQue.pop();
        sortedOut.push_back(readyNode);

        Node* adjNode = m_adjMap.at(readyNode);
        size_t neighborCount = adjNode->neighbors.size();
        for(auto i = 0; i < neighborCount; i++)
        {
            T neighbor = adjNode->neighbors.at(i);
            indegreeMap[neighbor]--;
            if (indegreeMap[neighbor] == 0)
                readyQue.push(neighbor);
        }
    }
    
    return sortedOut;
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
size_t Graph<T, Hash, KeyEqual>::size() const
{
    return m_adjMap.size();
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