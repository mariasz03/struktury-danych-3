#ifndef MEASURE_HPP
#define MEASURE_HPP

#include <cstdint>
#include <random>

// Funkcja generująca losowy numer z zakresu od 0 do 4 294 967 295
uint32_t generateRandomNumberFromSeed(std::mt19937 &gen) {  
    std::uniform_int_distribution<uint32_t> dis(0, std::numeric_limits<uint32_t>::max());
    return dis(gen);
}
// Funkcja generujaca (amountOfData) losowych liczb w strukturze (container) na podstawie ziarna (seed)
template<typename T>
void fillContainerWithRandomData(T& container, int amountOfData, int seed) { 
    std::mt19937 gen(seed);
    for (int i = 0; i < amountOfData; i++) {
        container.insert(generateRandomNumberFromSeed(gen), generateRandomNumberFromSeed(gen));
    }
}

#endif