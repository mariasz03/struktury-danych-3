#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include "Entry.hpp"
#include <cstdint>
#include <iostream>

class HashTable {
public:
    HashTable(int initialCapacity) : capacity(initialCapacity), size(0) { // Konstruktor
        table = new Entry[capacity];
        for (int i = 0; i < capacity; ++i) {
            table[i].occupied = false;
        }
    }

    HashTable(const HashTable &other) { // Konstruktor kopiujacy
        size = other.size;
        capacity = other.capacity;
        table = new Entry[capacity];
        for (int i = 0; i < size; ++i) {
            table[i] = other.table[i];
        }
    }

    ~HashTable() { // Destruktor
        delete[] table;
    }

    virtual void insert(uint32_t key, uint32_t value) = 0; // Metoda dodawania elementu o kluczu key i wartosci value
    virtual bool remove(uint32_t key) = 0; // Metoda usuwania elementu o kluczu key
    virtual uint32_t search(uint32_t key) const = 0; // Metoda zwracajaca wartosc dla podanego klucza
    virtual void print() const = 0; // Metoda wyswietlajaca tablice
    int getSize() { // Metoda zwraca rozmiar tablicy
        return size;
    }; 
    int getCapacity() { // Metoda zwraca pojemnosc tablicy
        return capacity;
    };
    float getLoadFactor() { // Metoda zwraca load factor tablicy
        return static_cast<float>(this->size)/(this->capacity);
    };
protected:
    int capacity;
    int size; 
    Entry* table;

    virtual void rehash() = 0; // Metoda zwiekszajaca rozmiar tablicy oraz wykonujaca ponowne mieszanie
    virtual int hash(uint32_t key, int attempt) const = 0; // Metoda funkcji obliczajacej indeks na podstawie klucza
};

#endif
