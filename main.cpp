#include "headers/OpenAddressingTable.hpp"
#include "headers/ClosedAddressingTable.hpp"
#include "headers/CuckooHashingTable.hpp"

#include "headers/Timer.hpp"
#include "measure.hpp"
#include "generate_data.hpp"
#include <cstdlib>

template <typename T>
void performOperations(T& map) {
    int operationMenu;
    uint32_t value, key;
    while (true) {
        std::cout << std::endl << "Wybierz operacje: " << std::endl;
        std::cout << "1. Dodaj pare klucz-wartosc do slownika." << std::endl; 
        std::cout << "2. Usun pare klucz-wartosc do slownika." << std::endl; 
        std::cout << "3. Znajdz wartosc przypisana do klucza." << std::endl; 
        std::cout << "4. Wyswietl elementy slownika." << std::endl; 
        std::cout << "5. Wygeneruj losowe dane." << std::endl; 
        std::cout << "6. Powrot do menu glownego." << std::endl;
        std::cout << "Wybierz: ";
        std::cin >> operationMenu;
        switch (operationMenu) {
            case 1: {
                std::cout << "Podaj wartosc elementu: ";
                std::cin >> value;
                std::cout << "Podaj klucz elementu: ";
                std::cin >> key;
                map.insert(key, value);
                std::cout << "Element zostal dodany.";
                break;
            }
            case 2: {
                std::cout << "Podaj klucz elementu ktory chcesz usunac: ";
                std::cin >> key;
                if (map.remove(key)) {
                    std::cout << "Pomyslnie usunieto element.";
                } else {
                    std::cout << "Nie udalo sie usunac elementu.";
                }
                break;
            }
            case 3: {
                std::cout << "Podaj klucz elementu ktorego wartosc chcesz znalezc: ";
                std::cin >> key;
                try {
                    std::cout << "Wartosc elementu o kluczu " << key << ": " << map.search(key);
                } catch (const std::runtime_error& e) {
                    std::cerr << "Blad: " << e.what() << std::endl;
                    break;
                }
                break;
            }
            case 4: {
                map.print();
                break;
            }
            case 5: {
                int seed = rand();
                int amountOfData;
                std::cout << "Podaj ile danych chcesz wygenerowac: ";
                std::cin >> amountOfData;
                fillContainerWithRandomData(map, amountOfData, seed);
                break;
            }
            case 6: 
                return;
            default:
                std::cout << "Niepoprawny wybor opcji.";
                break;
        }
    }
}

int main() {
    srand(time(NULL));
    while (true) {
        int structureMenu;
        std::cout << std::endl << "Wybierz rodzaj implementacji slownika:" << std::endl;
        std::cout << "1. Slownik w oparciu o tablice mieszajaca z adresowaniem otwartym. " << std::endl;
        std::cout << "2. Slownik w oparciu o tablice mieszajaca z adresowaniem zamknietym BST." << std::endl;
        std::cout << "3. Slownik w oparciu o tablice mieszajaca z haszowaniem kukulczym." << std::endl;
        std::cout << "4. Wykonaj pomiary wszystkich struktur." << std::endl;
        std::cout << "5. Wyjdz z programu." << std::endl;
        std::cout << "Wybierz: ";
        std::cin >> structureMenu;
        switch (structureMenu) {
            case 1: {
                OpenAddressingTable openTable;
                performOperations(openTable);
                break;
            }
            case 2: {
                ClosedAddressingTable closedTable;
                performOperations(closedTable);
                break;
            }
            case 3: {
                CuckooHashingTable cuckooTable;
                performOperations(cuckooTable);
                break;
            }
            case 4: {
                // Tablica ziaren oraz inicjalizacja
                int seeds[5]; 
                for (int i = 0; i < 5; i++) {
                    seeds[i] = rand();
                }
                // Tablica elementow oraz priorytetow ktore sa wykorzystane podczas uzycia funkcji insert i modifyKey, generowane losowo
                uint32_t value[5]; 
                uint32_t key[5];
                for (int i = 0; i < 5; i++) {
                    std::mt19937 gen(seeds[i]);
                    value[i] = generateRandomNumberFromSeed(gen);
                    key[i] =  generateRandomNumberFromSeed(gen);
                    std::cout << std::endl << i+1 << ". Seed: " << seeds[i] << std::endl << "wartosc: "  << value[i] << "," << std::endl << "klucz: " << key[i] << std::endl;
                }
                // Punkty pomiarowe - zestawy danych o roznej wielkosci do pomiaru. Dla kazdego seedu 9 roznych wielkosci danych
                int dataSetSize[9] = {1000, 5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000};
                measureAndSave("CUCKOO_INSERT", CUCKOO, INSERT, 9, dataSetSize, 5, seeds, 100, value, key);
                measureAndSave("CUCKOO_REMOVE", CUCKOO, REMOVE, 9, dataSetSize, 5, seeds, 100, value, key);
                measureAndSave("OPEN_INSERT", OPEN, INSERT, 9, dataSetSize, 5, seeds, 100, value, key);
                measureAndSave("OPEN_REMOVE", OPEN, REMOVE, 9, dataSetSize, 5, seeds, 100, value, key);
                measureAndSave("CLOSED_INSERT", CLOSED, INSERT, 9, dataSetSize, 5, seeds, 100, value, key);
                measureAndSave("CLOSED_REMOVE", CLOSED, REMOVE, 9, dataSetSize, 5, seeds, 100, value, key);
                std::cout << "Pomiary zostaly wykonane i zapisane w pliku.";
                break;
            }
            case 5: 
                return 0;
            default:
                std::cout << "Niepoprawny wybor opcji menu." << std::endl;
                break;
        }
    }
}
