#ifndef CUCKOOHASHINGTABLE_HPP
#define CUCKOOHASHINGTABLE_HPP

#include "HashTable.hpp"

#include <iostream>
#include <cmath>
#include <cstdlib>


class CuckooHashingTable : public HashTable {
public:
    CuckooHashingTable(int initialCapacity);
    ~CuckooHashingTable();
    void insert(int key, int value) override;
    bool remove(int key) override;
    int search(int key) const override;

protected:
    void rehash() override;
    int hash(int key, int attempt) const override;

private:
    Entry* table2;
    void rehash(int newCapacity);
    void swap(int& key1, int& value1, int& key2, int& value2);
};

#endif
