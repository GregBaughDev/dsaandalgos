#include "./trie.h"
#include <iostream>
void Trie::insertWord(const std::string &word)
{
    TrieNode *currNode = rootNode.get();

    for (auto &c : word)
    {
        if (currNode->children.find(c) == currNode->children.end())
        {
            currNode->children.insert({c, std::make_unique<TrieNode>()});
        }
        
        currNode = currNode->children[c].get();
    }

    currNode->endOfWord = true;
}

bool Trie::search(const std::string &word) const
{
    TrieNode *currNode = rootNode.get();

    for (auto &c : word)
    {
        if (currNode->children.find(c) != currNode->children.end())
        {
            currNode = currNode->children[c].get();
        }

        if (currNode->endOfWord)
        {
            return true;
        }
    }

    return false;
}

bool Trie::startsWith(const std::string &prefix) const
{
    TrieNode *currNode = rootNode.get();

    for (auto &c : prefix)
    {
        if (currNode->children.find(c) == currNode->children.end())
        {
            return false;
        }

        currNode = currNode->children[c].get();
    }

    return true;
}

