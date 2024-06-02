#ifndef CLOSED_ADDRESSING_TABLE_HPP
#define CLOSED_ADDRESSING_TABLE_HPP

#include "BalancedBST.hpp"

class ClosedAddressingTable {
public:
    ClosedAddressingTable(int initialCapacity = 10);
    ClosedAddressingTable(const ClosedAddressingTable& other);
    ~ClosedAddressingTable();

    void insert(uint32_t key, uint32_t value);
    bool remove(uint32_t key);
    uint32_t search(uint32_t key) const;

    void print() const;
    
private:
    int hash(uint32_t key) const;
    void copyFrom(const ClosedAddressingTable& other); // Funkcja kopiujaca jedna tablice do drugiej

    int capacity;
    int size;
    BalancedBST* buckets; // Tablica zbalansowanych drzew binarnych
};

#endif