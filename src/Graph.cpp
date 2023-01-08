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
    if (!m_adjMap.contains(node))
        m_adjMap.insert(node, new Node(node));
}

template <typename T, class Hash, class KeyEqual>
void Graph<T, Hash, KeyEqual>::addEdge(const T &firstNode, const T &secondNode, const bool &bidirectional, const size_t& weight)
{
    if (!m_adjMap.contains(firstNode))
        m_adjMap.insert(firstNode, new Node(firstNode));
    if (!m_adjMap.contains(secondNode))
        m_adjMap.insert(secondNode, new Node(secondNode));
    
    Node* adjNode;
    size_t pos;

    if (bidirectional){
        adjNode = m_adjMap.at(secondNode);
        pos = findNeighbor(adjNode, firstNode);
        if (pos == -1)
            adjNode->neighbors.push_back({firstNode, weight});
        else
            adjNode->neighbors[pos].second = weight;
    }
    
    adjNode = m_adjMap.at(firstNode);
    pos = findNeighbor(adjNode, secondNode);
    if (pos == -1)
        adjNode->neighbors.push_back({secondNode, weight});
    else
        adjNode->neighbors[pos].second = weight;
}

template <typename T, class Hash, class KeyEqual>
void Graph<T, Hash, KeyEqual>::removeEdge(const T &firstNode, const T &secondNode, const bool& bothDirections)
{
    Node* adjNode;
    size_t pos;
    
    if (m_adjMap.contains(firstNode)){
        adjNode = m_adjMap.at(firstNode);
        if (adjNode != nullptr){
            pos = findNeighbor(adjNode, secondNode);
            if (pos != -1)
                adjNode->neighbors.remove(pos);
        }
    }

    if (bothDirections && m_adjMap.contains(secondNode)){
        adjNode = m_adjMap.at(secondNode);
        if (adjNode != nullptr){
            pos = findNeighbor(adjNode, firstNode);
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
        auto neighbor = adjNode->neighbors.front();
        removeEdge(node, neighbor.first, true);
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
    return m_adjMap.contains(firstNode) && findNeighbor(m_adjMap.at(firstNode), secondNode) != -1;
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
            T neighbor = adjNode->neighbors.at(i).first;
            if (!visitedMap.contains(neighbor)){
                nodeQue.push(neighbor);
                visitedMap.insert(neighbor, true);
            }
        }
    }
    
    return bfsOut;
}

template <typename T, class Hash, class KeyEqual>
void Graph<T, Hash, KeyEqual>::dfsHelper(const T &node, Vector<T>& dfsOut, Hashmap<T,bool,Hash,KeyEqual> &visitedMap) const
{
    visitedMap.insert(node, true);
    dfsOut.push_back(node);

    Node* adjNode = m_adjMap.at(node);
    size_t neighborCount = adjNode->neighbors.size();
    for(auto i = 0; i < neighborCount; i++)
    {
        T neighbor = adjNode->neighbors.at(i).first;
        if (!visitedMap.contains(neighbor))
            dfsHelper(neighbor, dfsOut, visitedMap);
    }
}

template <typename T, class Hash, class KeyEqual>
size_t Graph<T, Hash, KeyEqual>::findNeighbor(Node* adjNode, const T& node) const
{
    if (adjNode == nullptr)
        return -1;
    
    size_t neighborCount = adjNode->neighbors.size();
    size_t neighborPos = -1;
    KeyEqual match;
    
    for(auto i = 0; i < neighborCount; i++)
    {
        if (match(adjNode->neighbors.at(i).first, node)){
            neighborPos = i;
            break;
        }
    }

    return neighborPos;
}

template <typename T, class Hash, class KeyEqual>
bool Graph<T, Hash, KeyEqual>::traverse(const T &node, const T& dest, size_t& pathSum, const size_t& targetSum, Vector<T> &path, Hashmap<T, bool, Hash, KeyEqual> &visitedMap) const
{
    KeyEqual nodeEqual;
    Node *adjNode = m_adjMap.at(node);
    size_t neighborCount = adjNode->neighbors.size();
    
    path.push_back(node);
    visitedMap.insert(node, true);

    for(auto i = 0; i < neighborCount; i++)
    {
        T neighbor = adjNode->neighbors.at(i).first;
        size_t weight = adjNode->neighbors.at(i).second;

        if (pathSum + weight >= targetSum){
            if (pathSum + weight == targetSum){
                if (nodeEqual(dest, neighbor)){
                    path.push_back(neighbor);
                    return true;
                }
            }
            else
                continue;
        }
        if (!visitedMap.contains(neighbor) || (visitedMap.contains(neighbor) && visitedMap.at(neighbor) == false)){
            pathSum += weight;
            if (!traverse(neighbor, dest, pathSum, targetSum, path, visitedMap)){
                visitedMap[neighbor] = false;
                pathSum -= weight;
                path.pop_back();
            }
            else
                return true;
        }
    }
    return false;
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
            indegreeMap[adjNode->neighbors.at(i).first]++;
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
            T neighbor = adjNode->neighbors.at(i).first;
            indegreeMap[neighbor]--;
            if (indegreeMap[neighbor] == 0)
                readyQue.push(neighbor);
        }
    }
    
    return sortedOut;
}

template <typename T, class Hash, class KeyEqual>
size_t Graph<T, Hash, KeyEqual>::shortestPath(const T &source, const T &dest, Vector<T> &path) const
{
    size_t shortestValue = shortestPath(source, dest);
    if (shortestValue == SIZE_MAX)
        return SIZE_MAX;
    
    path.clear();
    Hashmap<T,bool,Hash,KeyEqual> visitedMap;
    size_t pathSum = 0;
    traverse(source, dest, pathSum, shortestValue, path, visitedMap);

    return shortestValue;
}

template <typename T, class Hash, class KeyEqual>
size_t Graph<T, Hash, KeyEqual>::shortestPath(const T &source, const T &dest) const
{
    if (!m_adjMap.contains(source) || !m_adjMap.contains(dest))
        return SIZE_MAX;
    
    Hashmap<T,size_t,Hash,KeyEqual> weightMap;
    std::set<Pair<T,size_t>> traversalUpdate;

    weightMap.insert(source, 0);
    traversalUpdate.insert({source, 0});

    while (!traversalUpdate.empty())
    {
        auto itr = traversalUpdate.begin();
        T node = itr->first;
        size_t weightTillNow = itr->second;
        traversalUpdate.erase(itr);

        Node* adjNode = m_adjMap.at(node);
        size_t neighborCount = adjNode->neighbors.size();
        for(auto i = 0; i < neighborCount; i++)
        {
            T neighbor = adjNode->neighbors.at(i).first;
            size_t weight = adjNode->neighbors.at(i).second;

            if (!weightMap.contains(neighbor) || (weightTillNow + weight < weightMap.at(neighbor))){
                auto itr = traversalUpdate.find({neighbor, weightMap.contains(neighbor) ? weightMap.at(neighbor) : SIZE_MAX});
                if (itr != traversalUpdate.end())
                    traversalUpdate.erase(itr);

                weightMap.insert(neighbor, weightTillNow + weight);
                traversalUpdate.insert({neighbor, weightTillNow + weight});
            }
        }
    }
    
    return weightMap.contains(dest) ? weightMap.at(dest) : SIZE_MAX;
}

template <typename T, class Hash, class KeyEqual>
List<T> Graph<T, Hash, KeyEqual>::neighbors(const T &node) const
{
    if (!m_adjMap.contains(node))
        return {};
    
    Node* adjNode = m_adjMap.at(node);
    size_t neighborCount = adjNode->neighbors.size();
    List<T> neighborNodes;

    for(auto i = 0; i < neighborCount; i++)
    {
        neighborNodes.push_back(adjNode->neighbors.at(i).first);
    }

    return neighborNodes;
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
    m_adjMap.clear();
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