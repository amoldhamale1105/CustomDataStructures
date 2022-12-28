#include "Trie.hpp"

Trie::Trie()
{
    m_root = new Node('\0');
}

Trie::~Trie()
{
    delete m_root;
}

void Trie::insert(const std::string &data)
{
    if (data.empty())
        return;
    
    const char* charArr = data.c_str();
    Node* node = m_root;

    while (*charArr != '\0')
    {
        if (node->m_children.contains(*charArr)){
            node = node->m_children[*charArr];
        }
        else{
            Node* newChild = new Node(*charArr);
            node->m_children.insert(*charArr, newChild);
            node = newChild;
        }
        charArr++;
    }

    node->m_endOfWord = true;
}

bool Trie::contains(const std::string &data) const
{
    bool found{true};
    const char* charArr = data.c_str();
    Node* node = m_root;

    while (*charArr != '\0')
    {
        if (node->m_children.contains(*charArr)){
            node = node->m_children[*charArr];
        }
        else{
            found = false;
            break;
        }
        charArr++;
    }

    return found && node->m_endOfWord;
}
