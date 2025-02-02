#include "./hashtable.h"

#include <iostream>
#include <algorithm>

int HashTable::hash(const std::string &key)
{
    return hashFnv1a(key) % m_table.capacity();
}

u_int64_t HashTable::hashFnv1a(const std::string &key)
{
    u_int64_t hashValue = m_FNV_OFFSET;
    for (int i = 0; i < key.length(); i++)
    {
        hashValue ^= key.at(i);
        hashValue *= m_FNV_PRIME;
    }
    return hashValue;
}

bool HashTable::put(const std::string &key, const int &value)
{
    int index = hash(key);

    if (m_table.at(index).index() == 0) // variant is pair
    {
        return handlePairVariant(key, value, index);
    }

    if (m_table.at(index).index() == 1) // variant is vector
    {
        return handleVecVariant(key, value, index);
    } 

    throw std::runtime_error("Unable to put" + key + " : " + std::to_string(value) + " into table");
}

bool HashTable::handlePairVariant(const std::string &key, const int &value, const int &index)
{
    auto pairPtr = std::get_if<optVariant>(&m_table.at(index));

    if (pairPtr->has_value()) // get the value from here
    {
        if (pairPtr->value().first == key)
        {
            throw std::runtime_error(key + " already has value assigned");
        }

        // there is a collision, so change the type to a vector
        // create the vector and add the existing and new items to it
        auto newVector = std::vector<tablePair>{};

        newVector.emplace_back(pairPtr->value().first, pairPtr->value().second);
        newVector.emplace_back(key, value);
        // set the vector to be the new value at this point in the map
        m_table.at(index) = newVector;
        m_size++;
        return true;
    }

    // no current value at this position
    pairPtr->emplace(key, value);
    m_size++;
    return true;
}

bool HashTable::handleVecVariant(const std::string &key, const int &value, const int &index)
{
    auto vecPtr = std::get_if<std::vector<tablePair>>(&m_table.at(index));
    
    if (
        std::any_of(vecPtr->begin(), vecPtr->end(),
            [&key] (const tablePair &p) {
                return p.first == key;
            }
        )
    )
    {
        // key already exists
        throw std::runtime_error(key + " already has value assigned");
    }

    // put it at the back of the existing bucket
    vecPtr->emplace_back(key, value);
    m_size++;
    return true;
}

bool HashTable::containsKey(const std::string &key)
{
    int index = hash(key);

    if (m_table.at(index).index() == 0) // pair
    {
        auto kVPair = std::get_if<optVariant>(&m_table.at(index));

        if (kVPair->has_value() && kVPair->value().first == key)
        {
            return true;
        }
    }

    if (m_table.at(index).index() == 1) // vec
    {
        auto bucket = std::get_if<vecVariant>(&m_table.at(index));

        for (auto &b : *bucket)
        {
            if (b.first == key)
            {
                return true;
            }
        }
    }

    return false;
}

bool HashTable::containsValue(const int &value)
{
    for (auto &item : m_table)
    {
        if (item.index() == 0) // pair
        {
            auto kVPair = std::get_if<optVariant>(&item);

            if (kVPair->has_value() && kVPair->value().second == value)
            {
                return true;
            }
        }
        
        if (item.index() == 1) // vector
        {
            auto bucket = std::get_if<vecVariant>(&item);

            for (auto &b : *bucket)
            {
                if (b.second == value)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

int HashTable::get(const std::string &key)
{
    int index = hash(key);

    if (m_table.at(index).index() == 0) // pair
    {
        auto kVPair = std::get_if<optVariant>(&m_table.at(index));

        if (kVPair->has_value() && kVPair->value().first == key)
        {
            return kVPair->value().second;
        }
    }

    if (m_table.at(index).index() == 1) // vec
    {
        auto bucket = std::get_if<vecVariant>(&m_table.at(index));

        for (auto &b : *bucket)
        {
            if (b.first == key)
            {
                return b.second;
            }
        }
    }

    throw std::runtime_error("Key " + key + " not found in the table");
}

bool HashTable::replace(const std::string &key, const int &value)
{
    int index = hash(key);

    if (m_table.at(index).index() == 0) // pair
    {
        auto kVPair = std::get_if<optVariant>(&m_table.at(index));

        if (kVPair->has_value() && kVPair->value().first == key)
        {
            kVPair->value().second = value;
            return true;
        }
    }

    if (m_table.at(index).index() == 1) // vec
    {
        auto bucket = std::get_if<vecVariant>(&m_table.at(index));

        for (auto &b : *bucket)
        {
            if (b.first == key)
            {
                b.second = value;
                return true;
            }
        }
    }

    throw std::runtime_error("Unable to replace " + key + " as it doesn't exist");
}

int HashTable::remove(const std::string &key)
{
    int index = hash(key);

    if (m_table.at(index).index() == 0) // pair
    {
        auto kVPair = std::get_if<optVariant>(&m_table.at(index));

        if (kVPair->has_value() && kVPair->value().first == key)
        {
            int toReturn = kVPair->value().second;
            kVPair->reset();
            m_size--;
            return toReturn;
        }
    }

    if (m_table.at(index).index() == 1) // vec
    {
        auto bucket = std::get_if<vecVariant>(&m_table.at(index));

        for (int i = 0; i < bucket->capacity(); i++)
        {
            if (bucket->at(i).first == key)
            {
                int toReturn = bucket->at(i).second;
                bucket->erase(bucket->begin() + i);
                m_size--;
                return toReturn;
            }
        }
    }

    throw std::runtime_error("Unable to remove " + key + " as it doesn't exist");
}

void HashTable::clear()
{
    for (auto &t : m_table)
    {
        t = std::nullopt;
    }

    m_size = 0;
}

int HashTable::size()
{
    return m_size;
}

void HashTable::print()
{
    for (int i = 0; i < m_table.capacity(); i++)
    {
        std::cout << "| " << i << " | ";

        if (m_table.at(i).index() == 0) // pair
        {
            auto kVPtr = std::get_if<optVariant>(&m_table.at(i));
            if (kVPtr->has_value())
            {
                std::cout << kVPtr->value().first << " | " << kVPtr->value().second << "\n";
            }
            else
            {
                std::cout << "No value\n";
            }
        }
        else // vector
        {
            std::cout << "bucket:\n";
            auto vecPtr = std::get_if<vecVariant>(&m_table.at(i));
            for (auto &idx : *vecPtr)
            {
                std::cout << "\t" << idx.first << " | " << idx.second << "\n";
            }
        }
    }
}