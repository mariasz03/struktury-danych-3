#include "../headers/ClosedAddressingTable.hpp"
#include <iostream>

ClosedAddressingTable::ClosedAddressingTable(int initialCapacity) : capacity(initialCapacity), size(0) {
    buckets = new BalancedBST[capacity];
}

ClosedAddressingTable::ClosedAddressingTable(const ClosedAddressingTable& other) {
    copyFrom(other);
}

ClosedAddressingTable::~ClosedAddressingTable() {
    delete[] buckets;
}

void ClosedAddressingTable::copyFrom(const ClosedAddressingTable& other) {
    capacity = other.capacity;
    size = other.size;
    buckets = new BalancedBST[capacity];
    for (int i = 0; i < capacity; ++i) {
        buckets[i] = other.buckets[i];
    }
}

void ClosedAddressingTable::insert(uint32_t key, uint32_t value) {
    int index = hash(key); // Obliczenie indeksu funkcja haszujaca
    if (buckets[index].insert(key, value)) { // Wstawienie elementu do drzewa binarnego
        size++; // Jezeli wstawiono z powodzeniem, zwiekszenie rozmiaru
    }
}

bool ClosedAddressingTable::remove(uint32_t key) {
    int index = hash(key); // Obliczenie indeksu funkcja haszujaca
    bool removed = buckets[index].remove(key); // Usuniecie elementu z drzewa binarnego
    if (removed) {
        size--; // Jezeli usunieto z powodzeniem, zmniejszenie rozmiaru
    }
    return removed;
}

uint32_t ClosedAddressingTable::search(uint32_t key) const {
    int index = hash(key); // Obliczenie indeksu funkcja haszujaca
    return buckets[index].search(key); // Wyszukanie elementu w drzewie binarnym
}

void ClosedAddressingTable::print() const {
    for (int i = 0; i < capacity; ++i) {
        std::cout << "Kubelek " << i << ": ";
        buckets[i].print();
        std::cout << std::endl;
    }
}

int ClosedAddressingTable::hash(uint32_t key) const {
    return key % capacity;
}