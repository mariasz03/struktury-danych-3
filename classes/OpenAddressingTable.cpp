#include "../headers/OpenAddressingTable.hpp"

void OpenAddressingTable::insert(int key, int value) {
    if (size >= capacity) {
        rehash();
    }
    int attempt = 0;
    int index = hash(key, attempt);
    while (table[index].occupied) {
        if (table[index].key == key) {
            table[index].value = value;
            return;
        }
        index = linearProbe(key, ++attempt);
    }
    table[index].key = key;
    table[index].value = value;
    table[index].occupied = true;
    size++;
}

bool OpenAddressingTable::remove(int key) {
    int attempt = 0;
    int index = hash(key, attempt);
    while (table[index].occupied) {
        if (table[index].key == key) {
            table[index].occupied = false;
            size--;
            return true;
        }
        index = linearProbe(key, ++attempt);
    }
    return false;
}

int OpenAddressingTable::search(int key) const {
    int attempt = 0;
    int index = hash(key, attempt);
    while (table[index].occupied) {
        if (table[index].key == key) {
            return table[index].value;
        }
        index = linearProbe(key, ++attempt);
    }
    return -1;
}

int OpenAddressingTable::linearProbe(int key, int attempt) const {
    return (hash(key, 0) + attempt) % capacity;
}

void OpenAddressingTable::rehash() {
    int newCapacity = capacity * 2;
    Entry* newTable = new Entry[newCapacity];
    for (int i = 0; i < newCapacity; ++i)
        newTable[i].occupied = false;

    for (int i = 0; i < capacity; ++i) {
        if (table[i].occupied) {
            int key = table[i].key;
            int value = table[i].value;
            int attempt = 0;
            int newIndex = hash(key, attempt);
            while (newTable[newIndex].occupied) {
                newIndex = (newIndex + 1) % newCapacity;
            }
            newTable[newIndex] = {key, value, true};
        }
    }
    delete[] table;
    table = newTable;
    capacity = newCapacity;
}

int OpenAddressingTable::hash(int key, int attempt) const {
    return (key + attempt) % capacity;
}
