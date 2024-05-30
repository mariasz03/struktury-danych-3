#ifndef OPENADDRESSINGTABLE_HPP
#define OPENADDRESSINGTABLE_HPP

#include "HashTable.hpp"

class OpenAddressingTable : public HashTable {
public:
    OpenAddressingTable(int initialCapacity) : HashTable(initialCapacity) {}

    void insert(int key, int value) override;
    bool remove(int key) override;
    int search(int key) const override;

protected:
    void rehash() override;
    int hash(int key, int attempt) const override;

private:
    int linearProbe(int key, int attempt) const;
};

#endif
