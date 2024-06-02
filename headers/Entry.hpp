#ifndef ENTRY_HPP
#define ENTRY_HPP

#include <cstdint>

struct Entry {
        uint32_t key; // Klucz
        uint32_t value; // Wartosc
        bool occupied; // Flaga okreslajaca, czy kubelek jest zajety
};

#endif