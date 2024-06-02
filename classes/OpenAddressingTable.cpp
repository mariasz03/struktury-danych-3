#include "../headers/OpenAddressingTable.hpp"

void OpenAddressingTable::insert(uint32_t key, uint32_t value) {
    if (size >= capacity * 0.5) { // Jezeli loadfactor przekroczy 0.5, tablica jest rehashowana
        rehash();
    }
    int attempt = 0; // Licznik prob wstawienia elementu do kubelka
    int index = hash(key, attempt); // Obliczanie indeksu na podstawie klucza i proby
    while (table[index].occupied) {
        if (table[index].key == key) { // Jezeli klucz jest taki sam, aktualizacja wartosci
            table[index].value = value;
            return;
        }
        index = linearProbe(key, ++attempt); // Obliczenie indeksu nastepnego kubelka
    }
    // Przypisanie wartosci i zwiekszenie rozmiaru
    table[index].key = key;
    table[index].value = value;
    table[index].occupied = true;
    size++;
}

bool OpenAddressingTable::remove(uint32_t key) {
    int attempt = 0; // Licznik prob usuniecia elementu z kubelka
    int index = hash(key, attempt); // Obliczanie indeksu na podstawie klucza i proby
    while (table[index].occupied) { 
        if (table[index].key == key) { // Jezeli klucz sie zgadza, usuniecie elementu
            table[index].occupied = false;
            size--;
            return true;
        }
        index = linearProbe(key, ++attempt);
    }
    return false; // Kiedy kubelek nie jest zajety, zwrocenie false
}

uint32_t OpenAddressingTable::search(uint32_t key) const {
    int attempt = 0; // Licznik prob wyszukania elementu 
    int index = hash(key, attempt); // Obliczanie indeksu na podstawie klucza i proby
    while (table[index].occupied) {
        if (table[index].key == key) { // Jezeli klucz sie zgadza, zwraca wartosc
            return table[index].value;
        }
        index = linearProbe(key, ++attempt); // Jezeli klucz sie nie zgadza, obliczenie nastepnej mozliwej lokalizacji elementu
    }
    throw std::runtime_error("Nie znaleziono elementu.");
}

void OpenAddressingTable::print() const {
    for (int i = 0; i < capacity; ++i) {
        if (table[i].occupied) {
            std::cout << "Kubelek " << i << ": (" << table[i].key << ", " << table[i].value << ")" << std::endl;
        } else {
            std::cout << "Kubelek " << i << ": Pusty" << std::endl;
        }
    }
}

void OpenAddressingTable::rehash() {
    int newCapacity = capacity * 2; // Zwiekszenie pojemnosci tablicy dwukrotnie
    Entry* newTable = new Entry[newCapacity];
    for (int i = 0; i < newCapacity; ++i) newTable[i].occupied = false;

    for (int i = 0; i < capacity; ++i) { // Przekopiowanie elementow do nowej tablicy, na nowe pozycje
        if (table[i].occupied) {
            uint32_t key = table[i].key;
            uint32_t value = table[i].value;
            int attempt = 0;
            int newIndex = hash(key, attempt);
            while (newTable[newIndex].occupied) { // Szukanie wolnej lokalizacji w przypadku gdy kubelek jest zajety
                newIndex = (newIndex + 1) % newCapacity;
            }
            newTable[newIndex] = {key, value, true};
        }
    }
    delete[] table;
    table = newTable;
    capacity = newCapacity;
}

int OpenAddressingTable::hash(uint32_t key, int attempt) const { // Funkcja mieszajaca na podstawie
    return (key + attempt) % capacity;
}

int OpenAddressingTable::linearProbe(uint32_t key, int attempt) const { // Funkcja znajdujaca nastepny mozliwy kubelek na podstawie klucza i proby
    return (hash(key, 0) + attempt) % capacity;
}
