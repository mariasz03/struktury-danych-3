#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include "Entry.hpp"

class HashTable {
public:
    HashTable(int initialCapacity) : capacity(initialCapacity), size(0) {
        table = new Entry[capacity];
        for (int i = 0; i < capacity; ++i) {
            table[i].occupied = false;
        }
    }

    virtual ~HashTable() {
        delete[] table;
    }

    virtual void insert(int key, int value) = 0;
    virtual bool remove(int key) = 0;
    virtual int search(int key) const = 0;
    int getSize() {
        return size;
    }; 
    int getCapacity() {
        return capacity;
    };
    float getLoadFactor() {
        return static_cast<float>(this->size)/(this->capacity);
    };
protected:
    int capacity;
    int size;
    Entry* table;

    virtual void rehash() = 0;
    virtual int hash(int key, int attempt) const = 0;
};

#endif
