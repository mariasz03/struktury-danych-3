#ifndef BST_NODE_HPP
#define BST_NODE_HPP

#include "BSTEntry.hpp"

struct BSTNode {
    BSTEntry entry;
    BSTNode* left; // Lewe dziecko
    BSTNode* right; // Prawe dziecko

    BSTNode(uint32_t key, uint32_t value) : entry{key, value}, left(nullptr), right(nullptr) {}
};

#endif