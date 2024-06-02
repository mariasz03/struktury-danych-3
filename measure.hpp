#include <iostream>
#include <fstream>
#include <string>

#include "headers/OpenAddressingTable.hpp"
#include "headers/ClosedAddressingTable.hpp"
#include "headers/CuckooHashingTable.hpp"

#include "headers/Timer.hpp"
#include "generate_data.hpp"

enum Function { // Funkcje ktore mozna zbadac
    INSERT,
    REMOVE  
};

enum HashTableType { // Rodzaje implementacji kolejki ktore mozna zbadac
    OPEN,
    CLOSED,
    CUCKOO
};
// Funkcja wykonujaca pojedynczy pomiar metody (func) kolejki (container). number i priority to liczby ktore sa potrzebne do
// wykonania operacji insert i modifyKey. Zwraca czas wykonania operacji w nanosekundach.
template<typename T>
double measure(T container, Function func, uint32_t value = 0, uint32_t key = 0) { 
    Timer timer;
    switch (func) {
        case INSERT:
            container.insert(key, value);
            break;
        case REMOVE:
            container.remove(key);
            break;   
    }
    return timer.elapsed();
};


// Funkcja mierzaca dana operacje podana liczbe razy (repetitions) i usredniajaca ten pomiar
template<typename T>
double measureAverage(T container, Function func, int repetitions, uint32_t value = 0, uint32_t key = 0) {
    double avg;
    double sum = 0;
    for (int i = 0; i < repetitions; i++) {
        sum += measure(container, func, value, key);
    }
    avg = sum / repetitions;
    return avg;
};

// Funkcja dla na podstawie ziaren (seed) generuje rozne rozmiary struktur (dataSetSize) oraz mierzy podana metode kolejki.
// Metoda na pojedynczym zestawie danych jest wykonywana repetitions razy i usredniana.
// Wyniki ze wszystkich ziaren dla kazdej operacji sa usredniane
// Wyniki zapisywane sa w pliku o sciezce measured/"file".csv
void measureAndSave(std::string filename, HashTableType hashTableType, Function func, int numberOfDataSets, int dataSetSize[], int numberOfSeeds, int seed[], int repetitions, uint32_t value[] = 0, uint32_t key[] = 0) {
    std::ofstream outputFile("measured/" + filename + ".csv");
    if (!outputFile.is_open()) {
        std::cerr << "Error occurred while opening file.";
        return;
    }
    for (int i = 0; i < numberOfDataSets; i++) {
        double totalTime = 0; // Czas operacji zsumowany z kazdego ziarna
        for (int j = 0; j < numberOfSeeds; j++) {
            double time = 0; // Sredni czas pojedynczej operacji
            switch (hashTableType) {
                case OPEN: {
                    OpenAddressingTable hashTable;
                    fillContainerWithRandomData(hashTable, dataSetSize[i], seed[j]);
                    time = measureAverage(hashTable, func, repetitions, value[j], key[j]);
                    break;
                }
                case CLOSED: {
                    ClosedAddressingTable hashTable(100);
                    fillContainerWithRandomData(hashTable, dataSetSize[i], seed[j]);
                    time = measureAverage(hashTable, func, repetitions, value[j], key[j]);
                    break;
                }
                case CUCKOO: {
                    CuckooHashingTable hashTable;
                    fillContainerWithRandomData(hashTable, dataSetSize[i], seed[j]);
                    time = measureAverage(hashTable, func, repetitions, value[j], key[j]);
                    break;
                }
            }
            totalTime += time;
        }
        double avgTime = totalTime / numberOfSeeds; // Wynik usredniony z wszystkich ziaren
        outputFile << dataSetSize[i] << ", " << avgTime << std::endl;
    }
    outputFile.close();
}