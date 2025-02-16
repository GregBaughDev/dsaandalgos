#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

class Trie
{
public:
    Trie() 
    {
        rootNode = std::make_unique<TrieNode>();
    };
    void insertWord(const std::string &word);
    bool search(const std::string &word) const;
    bool startsWith(const std::string &prefix) const;

private:
class TrieNode
{
public:
    TrieNode() : children{} {};
    std::unordered_map<char, std::unique_ptr<TrieNode>> children;
    bool endOfWord = false;
};

std::unique_ptr<TrieNode> rootNode;
};

