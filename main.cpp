#include <iostream>
#include "headers/OpenAddressingTable.hpp"
#include "headers/CuckooHashingTable.hpp"
#include "headers/Timer.hpp"

int main() {
    // Test Open Addressing Table
    // Test Cuckoo Hashing Table
    std::cout << "\nOA Hashing Table Test:" << std::endl;
    OpenAddressingTable oaHashingTable(5);

    // Insert elements until the table is about to overflow
    for (int i = 0; i < 10; ++i) {
        oaHashingTable.insert(i, i * 100);
    }

    
    Timer timer1;
    oaHashingTable.insert(777, 10);
    int insTime = timer1.elapsed();
    std::cout << "Search: " << oaHashingTable.search(777) << std::endl;
    Timer timer2;
    oaHashingTable.remove(777);
    int removeTime = timer2.elapsed();
    std::cout << "Search: " << oaHashingTable.search(777) << std::endl;
    std::cout << "InsTime: " << insTime << " Remove time: " << removeTime << " Load factor: " << oaHashingTable.getLoadFactor() << std::endl;
    std::cout << "Size: " << oaHashingTable.getSize() << ", capacity:  " << oaHashingTable.getCapacity();
    return 0;
}
