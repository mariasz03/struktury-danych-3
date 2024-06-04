#include "../headers/CuckooHashingTable.hpp"

CuckooHashingTable::CuckooHashingTable(int initialCapacity) : HashTable(initialCapacity) { // Konstruktor inicjalizujacy druga tablice
    table2 = new Entry[initialCapacity];
    for (int i = 0; i < initialCapacity; ++i) {
        table2[i].occupied = false;
    }
}

CuckooHashingTable::~CuckooHashingTable() { // Destruktor usuwajacy druga tablice
    delete[] table2;
}

CuckooHashingTable::CuckooHashingTable(const CuckooHashingTable& other) : HashTable(other.capacity) { // Konstruktor kopiujacy obie tablice
    size = other.size;
    table = new Entry[capacity];
    for (int i = 0; i < capacity; ++i) {
        table[i] = other.table[i];
    }

    table2 = new Entry[capacity];
    for (int i = 0; i < capacity; ++i) {
        table2[i] = other.table2[i];
    }
}

void CuckooHashingTable::insert(uint32_t key, uint32_t value) {
    // Sprawdzenie, czy konieczne jest rehashowanie (loadfactor >= 0.5)
    if (size >= capacity * 0.5) {
        rehash();
    }

    int index1 = hash(key, 0); // Obliczenie indeksu pierwszej tablicy
    if (!table[index1].occupied) { // Jezeli miejsce jest wolne to wstawienie elementu do kubelka
        table[index1] = {key, value, true};
        ++size;
        return;
    }

    int index2 = hash(key, 1); // Obliczenie indeksu drugiej tablicy
    if (!table2[index2].occupied) { // Jezeli miejsce jest wolne to wstawienie elementu do kubelka
        table2[index2] = {key, value, true};
        ++size;
        return;
    }

    int loopLimit = log2(capacity) * 2; // Limit iteracji zapobiegajacy wpadniecia w cykl
    for (int i = 0; i < loopLimit; ++i) {
        swap(key, value, table[index1].key, table[index1].value); // Zmiana wartosci pomiedzy tablicami
        if (!table2[index2].occupied) { // Jezeli miejsce jest wolne wstawienie elementu do kubelka i zakonczenie wstawiania
            table2[index2] = {key, value, true};
            ++size;
            return;
        }
        swap(key, value, table2[index2].key, table2[index2].value); // Zamiana wartosci
        // Obliczenie nowego indeksu obu tablic
        index1 = hash(key, 0); 
        index2 = hash(key, 1);
    }

    rehash();
    insert(key, value);
}

bool CuckooHashingTable::remove(uint32_t key) {
    int index1 = hash(key, 0); // Obliczenie indeksu pierwszej tablicy
    if (table[index1].occupied && table[index1].key == key) { // Jezeli kubelek jest zajety i klucz sie zgadza, usuniecie elementu i zakonczenie usuwania
        table[index1].occupied = false;
        --size;
        return true;
    }

    int index2 = hash(key, 1); // Obliczenie indeksu drugiej tablicy
    if (table2[index2].occupied && table2[index2].key == key) { // Jezeli kubelek jest zajety i klucz sie zgadza, usuniecie elementu i zakonczenie usuwania
        table2[index2].occupied = false;
        --size;
        return true;
    }

    return false; // Kiedy nie udalo sie usunac elementu, zwrocenie false
}

uint32_t CuckooHashingTable::search(uint32_t key) const {
    int index1 = hash(key, 0); // Obliczenie pierwszego indeksu
    if (table[index1].occupied && table[index1].key == key) {  // Jezeli kubelek zajety i klucz sie zgadza, zwrocenie wartosci
        return table[index1].value;
    }

    int index2 = hash(key, 1); // Obliczenie drugiego indeksu
    if (table2[index2].occupied && table2[index2].key == key) { // Jezeli kubelek zajety i klucz sie zgadza, zwrocenie wartosci
        return table2[index2].value;
    }
    throw std::runtime_error("Nie znaleziono elementu.");
}

void CuckooHashingTable::print() const {
    std::cout << "Tablica 1:" << std::endl;
    for (int i = 0; i < capacity; ++i) {
        if (table[i].occupied) {
            std::cout << "Kubelek " << i << ": (" << table[i].key << ", " << table[i].value << ")" << std::endl;
        } else {
            std::cout << "Kubelek " << i << ": Pusty" << std::endl;
        }
    }

    std::cout << "Tablica 2:" << std::endl;
    for (int i = 0; i < capacity; ++i) {
        if (table2[i].occupied) {
            std::cout << "Kubelek " << i << ": (" << table2[i].key << ", " << table2[i].value << ")" << std::endl;
        } else {
            std::cout << "Kubelek " << i << ": Pusty" << std::endl;
        }
    }
}

void CuckooHashingTable::rehash() {
    // Obliczenie nowej pojemności tak, aby load factor był mniejszy niż 0.5
    int newCapacity = size * 4;
    rehash(newCapacity);
}

void CuckooHashingTable::rehash(int newCapacity) {
    // Inicjalizacja tablicy o nowym rozmiarze
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
    // Wstawienie elementow do tablicy o nowym rozmiarze
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

int CuckooHashingTable::hash(uint32_t key, int attempt) const {
    // Funkcja mieszajaca dla jednej i drugiej tablicy
    if (attempt % 2 == 0) {
        return key % capacity;
    } else {
        return (key / capacity) % capacity;
    }
}

void CuckooHashingTable::swap(uint32_t& key1, uint32_t& value1, uint32_t& key2, uint32_t& value2) {
    int tempKey = key1;
    int tempValue = value1;
    key1 = key2;
    value1 = value2;
    key2 = tempKey;
    value2 = tempValue;
}