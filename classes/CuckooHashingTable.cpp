#include "../headers/CuckooHashingTable.hpp"

CuckooHashingTable::CuckooHashingTable(int initialCapacity) : HashTable(initialCapacity) {
    table2 = new Entry[initialCapacity];
    for (int i = 0; i < initialCapacity; ++i) {
        table2[i].occupied = false;
    }
}

CuckooHashingTable::~CuckooHashingTable() {
    delete[] table2;
}

void CuckooHashingTable::insert(int key, int value) {
    // Sprawdzenie, czy konieczne jest rehashowanie
    if (size >= capacity / 2) {
        rehash();
    }

    int index1 = hash(key, 0);
    if (!table[index1].occupied) {
        table[index1] = {key, value, true};
        ++size;
        return;
    }

    int index2 = hash(key, 1);
    if (!table2[index2].occupied) {
        table2[index2] = {key, value, true};
        ++size;
        return;
    }

    int loopLimit = log2(capacity) * 2;
    for (int i = 0; i < loopLimit; ++i) {
        swap(key, value, table[index1].key, table[index1].value);
        if (!table2[index2].occupied) {
            table2[index2] = {key, value, true};
            ++size;
            return;
        }
        swap(key, value, table2[index2].key, table2[index2].value);
        index1 = hash(key, 0);
        index2 = hash(key, 1);
    }

    rehash();
    insert(key, value);
}

bool CuckooHashingTable::remove(int key) {
    int index1 = hash(key, 0);
    if (table[index1].occupied && table[index1].key == key) {
        table[index1].occupied = false;
        --size;
        return true;
    }

    int index2 = hash(key, 1);
    if (table2[index2].occupied && table2[index2].key == key) {
        table2[index2].occupied = false;
        --size;
        return true;
    }

    return false;
}

int CuckooHashingTable::search(int key) const {
    int index1 = hash(key, 0);
    if (table[index1].occupied && table[index1].key == key) {
        return table[index1].value;
    }

    int index2 = hash(key, 1);
    if (table2[index2].occupied && table2[index2].key == key) {
        return table2[index2].value;
    }

    return -1;
}

void CuckooHashingTable::rehash() {
    // Obliczenie nowej pojemności tak, aby load factor był mniejszy niż 0.5
    int newCapacity = size * 4;  // Ponieważ chcemy, aby load factor był mniejszy niż 0.5
    rehash(newCapacity);
}

void CuckooHashingTable::rehash(int newCapacity) {
    Entry* oldTable1 = table;
    Entry* oldTable2 = table2;
    int oldCapacity = capacity;

    capacity = newCapacity;
    table = new Entry[newCapacity];
    table2 = new Entry[newCapacity];

    for (int i = 0; i < newCapacity; ++i) {
        table[i].occupied = false;
        table2[i].occupied = false;
    }

    size = 0;

    for (int i = 0; i < oldCapacity; ++i) {
        if (oldTable1[i].occupied) {
            insert(oldTable1[i].key, oldTable1[i].value);
        }
        if (oldTable2[i].occupied) {
            insert(oldTable2[i].key, oldTable2[i].value);
        }
    }

    delete[] oldTable1;
    delete[] oldTable2;
}

int CuckooHashingTable::hash(int key, int attempt) const {
    if (attempt % 2 == 0) {
        return key % capacity;
    } else {
        return (key / capacity) % capacity;
    }
}

void CuckooHashingTable::swap(int& key1, int& value1, int& key2, int& value2) {
    int tempKey = key1;
    int tempValue = value1;
    key1 = key2;
    value1 = value2;
    key2 = tempKey;
    value2 = tempValue;
}