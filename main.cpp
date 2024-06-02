#include <iostream>

#include "headers/OpenAddressingTable.hpp"
#include "headers/ClosedAddressingTable.hpp"
#include "headers/CuckooHashingTable.hpp"

#include "headers/Timer.hpp"
#include "measure.hpp"
#include "generate_data.hpp"

int main() {
    int seeds[5]; 
    for (int i = 0; i < 5; i++) {
        seeds[i] = rand();
    }
    uint32_t value[5]; 
    uint32_t key[5];
    for (int i = 0; i < 5; i++) {
        std::mt19937 gen(seeds[i]);
        value[i] = generateRandomNumberFromSeed(gen);
        key[i] =  generateRandomNumberFromSeed(gen);
        std::cout << std::endl << i+1 << ". Seed: " << seeds[i] << std::endl << "Wartosc: "  << value[i] << "," << std::endl << "Klucz: " << key[i] << std::endl;
    }
    int dataSetSize[9] = {1000, 5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000};
    measureAndSave("CUCKOO_INSERT", CUCKOO, INSERT, 9, dataSetSize, 5, seeds, 100, value, key);
    measureAndSave("CUCKOO_REMOVE", CUCKOO, REMOVE, 9, dataSetSize, 5, seeds, 100, value, key);
    measureAndSave("OPEN_INSERT", OPEN, INSERT, 9, dataSetSize, 5, seeds, 100, value, key);
    measureAndSave("OPEN_REMOVE", OPEN, REMOVE, 9, dataSetSize, 5, seeds, 100, value, key);
    measureAndSave("CLOSED_INSERT", CLOSED, INSERT, 9, dataSetSize, 5, seeds, 100, value, key);
    measureAndSave("CLOSED_REMOVE", CLOSED, REMOVE, 9, dataSetSize, 5, seeds, 100, value, key);

    return 0;
}
