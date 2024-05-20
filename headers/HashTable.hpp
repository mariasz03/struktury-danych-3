#include <cstdint>

class HashTable {
public:
    virtual void insert(uint32_t key, uint32_t value) = 0;
    virtual void remove(uint32_t key) = 0;
    virtual ~HashTable() {};
protected:
    struct HashEntry {
        uint32_t key;
        uint32_t value;
        bool occupied;
    };
    static const int INITIAL_TABLE_SIZE = 50;
    int tableCapacity;
    int tableSize;
    virtual void rehash() = 0;
};