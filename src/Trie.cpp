#include "Trie.hpp"

Trie::Trie() : m_root(new Node('\0'))
{
}

Trie::Trie(const Trie &other) : m_root(new Node('\0'))
{
    Node* otherRoot = other.m_root;
    recursiveCopy(m_root, otherRoot);
}

Trie::~Trie()
{
    delete m_root;
}

void Trie::insert(const String &data)
{
    if (data.empty())
        return;
    
    const char* charArr = data.c_str();
    Node* node = m_root;

    while (*charArr != '\0')
    {
        if (!node->m_children.contains(*charArr)){
            Node* newChild = new Node(*charArr);
            node->m_children.insert(*charArr, newChild);
        }
        node = node->m_children[*charArr];
        charArr++;
    }

    node->m_endOfWord = true;
}

bool Trie::contains(const String &data) const
{
    if (data.empty())
        return false;
    
    bool found{true};
    const char* charArr = data.c_str();
    Node* node = m_root;

    while (*charArr != '\0')
    {
        if (!node->m_children.contains(*charArr)){
            found = false;
            break;
        }
        node = node->m_children[*charArr];
        charArr++;
    }

    return found && node->m_endOfWord;
}

void Trie::remove(const String &data)
{
    if (data.empty())
        return;
       
    Node* branchNode, *node;
    node = branchNode = m_root;
    const char* charArr = data.c_str();
    bool found{true};
    int charIndex{0}, branchIndex{0};

    while (*charArr != '\0')
    {
        if (!node->m_children.contains(*charArr)){
            found = false;
            break;
        }
        if (node->m_children.size() > 1){
            branchNode = node;
            branchIndex = charIndex;
        }
        node = node->m_children[*charArr];
        charArr++;
        charIndex++;
    }

    if (found && node->m_endOfWord){
        char branchChar = data.at(branchIndex);
        delete branchNode->m_children[branchChar];
        branchNode->m_children.erase(branchChar);
    }
}

void Trie::operator=(const Trie &other)
{
    if (m_root != nullptr)
        delete m_root;
    
    m_root = new Node('\0');
    Node* otherRoot = other.m_root;
    recursiveCopy(m_root, otherRoot);
}

void Trie::recursiveCopy(Node *node, Node* otherNode)
{
    if (otherNode == nullptr)
        return;
    
    Vector<char> keys = otherNode->m_children.keys();
    size_t total = keys.size();

    for(auto i = 0; i < total; i++)
    {
        char copyChar = keys.at(i);
        Node* otherNext = otherNode->m_children[copyChar];
        Node* copyNode = new Node(copyChar);
        copyNode->m_endOfWord = otherNext->m_endOfWord;
        node->m_children.insert(copyChar, copyNode);
        recursiveCopy(copyNode, otherNext);
    }
}
