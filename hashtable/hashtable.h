#pragma once

#include <vector>
#include <utility>
#include <variant>
#include <string>
#include <optional>

using tablePair = std::pair<std::string, int>;
using optVariant = std::optional<tablePair>;
using vecVariant = std::vector<tablePair>;
using tableType = std::variant<optVariant, vecVariant>;

class HashTable
{
public:
    HashTable(int size): m_table(size), m_size{0} {};
    bool containsKey(const std::string &key);
    bool containsValue(const int &value);
    int get(const std::string &key);
    bool put(const std::string &key, const int &value);
    int remove(const std::string &key);
    bool replace(const std::string &key, const int &value);
    int size();
    void print();
    void clear();
private:
    std::vector<tableType> m_table;
    int m_size;
    int hash(const std::string &key);
    bool handlePairVariant(const std::string &key, const int &value, const int &index);
    bool handleVecVariant(const std::string &key, const int &value, const int &index);
    u_int64_t hashFnv1a(const std::string &key);
    u_int64_t const m_FNV_PRIME = 0x100000001b3;
    u_int64_t const m_FNV_OFFSET = 0xcbf29ce48422325UL;
};