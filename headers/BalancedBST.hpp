#ifndef BALANCED_BST_HPP
#define BALANCED_BST_HPP

#include "BSTNode.hpp"
#include <iostream>

class BalancedBST { // Klasa Binary Search Tree
public:
    BalancedBST();
    ~BalancedBST();
    void insert(int key, int value);
    bool remove(int key);
    int search(int key) const;
private:
    BSTNode* root;
    BSTNode* insert(BSTNode* node, int key, int value);
    BSTNode* remove(BSTNode* node, int key, bool &removed);
    BSTNode* findMin(BSTNode* node) const;
    int search(BSTNode* node, int key) const;
    void destroyTree(BSTNode* node);
};

#endif