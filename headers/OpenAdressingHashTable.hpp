#include "HashTable.hpp"

class OpenAdressingHashTable : public HashTable {
private:
    HashEntry* table; 
    int hashFunction(uint32_t key);
    void rehash() override;
public:
    OpenAdressingHashTable();
    ~OpenAdressingHashTable();
    void insert(uint32_t key, uint32_t value) override;
    void remove(uint32_t key) override;
};