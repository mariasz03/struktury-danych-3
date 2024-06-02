#ifndef BALANCED_BST_HPP
#define BALANCED_BST_HPP

#include "BSTNode.hpp"

#include <iostream>

class BalancedBST {
public:
    BalancedBST();
    ~BalancedBST();
    BalancedBST& operator=(const BalancedBST& other); // Operator przypisania

    bool insert(uint32_t key, uint32_t value);
    bool remove(uint32_t key);
    uint32_t search(uint32_t key) const;

    void print() const;

private:
    BSTNode* root; // Korzen drzewa
    // Metody pomocnicze (do rekurencji)
    BSTNode* insert(BSTNode* node, uint32_t key, uint32_t value, bool& inserted);
    BSTNode* remove(BSTNode* node, uint32_t key, bool& removed);
    uint32_t search(BSTNode* node, uint32_t key) const;
    
    void destroyTree(BSTNode* node); // Metoda usuwajaca drzewo
    BSTNode* copyTree(BSTNode* node); // Metoda kopiujaca drzewo
    void print(BSTNode* node) const; // Funkcja pomocnicza do wypisywania elementow drzewa
    BSTNode* findMin(BSTNode* node) const; // Funkcja znajdujaca element o najmniejszym kluczu
};

#endif