#ifndef CUCKOOHASHINGTABLE_HPP
#define CUCKOOHASHINGTABLE_HPP

#include "HashTable.hpp"

#include <cmath>

class CuckooHashingTable : public HashTable {
public:
    CuckooHashingTable(int initialCapacity = 10);
    CuckooHashingTable(const CuckooHashingTable& other);
    ~CuckooHashingTable();
    
    void insert(uint32_t key, uint32_t value) override;
    bool remove(uint32_t key) override;
    uint32_t search(uint32_t key) const override;

    void print() const override;

private:
    Entry* table2; // Druga tablica, do ktorej zapisywany jest element gdy kubelek w pierwszej jest zajety
    void rehash() override;
    void rehash(int newCapacity);
    int hash(uint32_t key, int attempt) const override;
    void swap(uint32_t& key1, uint32_t& value1, uint32_t& key2, uint32_t& value2); // Metoda zamieniajaca ze soba dwie pary klucz-wartosc
};

#endif
