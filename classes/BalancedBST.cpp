#include "../headers/BalancedBST.hpp"

BalancedBST::BalancedBST() : root(nullptr) {};

BalancedBST::~BalancedBST() {
    destroyTree(root);
}

void BalancedBST::insert(int key, int value) {
    root = insert(root, key, value);
}

bool BalancedBST::remove(int key) {
    bool removed = false;
    root = remove(root, key, &removed);

}
