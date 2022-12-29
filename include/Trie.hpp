#pragma once

#include <Hashmap.hpp>

class Trie
{
    class Node
    {
        char m_ch;
        Hashmap<char, Node*> m_children;
        bool m_endOfWord;

    public:
        Node(const char& ch) : m_ch(ch), m_endOfWord(false) {}
        ~Node()
        {
            Vector<char> keys = m_children.keys();
            while (!keys.isEmpty())
            {
                char key = keys.pop_back();
                if (m_children.at(key) != nullptr)
                    delete m_children[key];
            }
        }
        friend class Trie;
    };

    Node* m_root;

public:
    Trie();
    virtual ~Trie();
    
    void insert(const std::string& data);
    bool contains(const std::string& data) const;
    void remove(const std::string& data);
};
