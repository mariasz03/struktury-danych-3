#ifndef BST_NODE_HPP
#define BST_NODE_HPP

#include "BSTEntry.hpp"

struct BSTNode {
    BSTEntry entry;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int k, int v) : entry{k, v}, left(nullptr), right(nullptr) {}
};

#endif