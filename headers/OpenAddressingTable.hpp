#ifndef OPENADDRESSINGTABLE_HPP
#define OPENADDRESSINGTABLE_HPP

#include "HashTable.hpp"

class OpenAddressingTable : public HashTable {
public:
    OpenAddressingTable(int initialCapacity = 10) : HashTable(initialCapacity) {} // Konstruktor, domyslnie tworzy tablice o pojemnosci 10

    void insert(uint32_t key, uint32_t value) override; 
    bool remove(uint32_t key) override;
    uint32_t search(uint32_t key) const override;
    void print() const override;

protected:
    void rehash() override;
    int hash(uint32_t key, int attempt) const override;

private:
    int linearProbe(uint32_t key, int attempt) const; // Metoda obliczajaca indeks kolejnego kubelka, gdy docelowy jest zajety
};

#endif
