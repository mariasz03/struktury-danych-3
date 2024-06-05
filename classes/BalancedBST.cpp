#include "../headers/BalancedBST.hpp"

BalancedBST::BalancedBST() : root(nullptr) {}

BalancedBST::~BalancedBST() {
    destroyTree(root);
}

BalancedBST& BalancedBST::operator=(const BalancedBST& other) {
    if (this != &other) {
        destroyTree(root);
        root = copyTree(other.root);
    }
    return *this;
}

bool BalancedBST::insert(uint32_t key, uint32_t value) {
    bool inserted = false;
    root = insert(root, key, value, inserted);
    return inserted;
}

bool BalancedBST::remove(uint32_t key) {
    bool removed = false;
    root = remove(root, key, removed);
    return removed;
}

uint32_t BalancedBST::search(uint32_t key) const {
    return search(root, key);
}

void BalancedBST::print() const {
    print(root);
}

// Rekurencyjna metoda wstawiania
BSTNode* BalancedBST::insert(BSTNode* node, uint32_t key, uint32_t value, bool& inserted) {
    if (node == nullptr) { // Jezeli obecny wezel jest nie istnieje, stworzenie nowy
        inserted = true;
        return new BSTNode(key, value);
    }
    if (key < node->entry.key) { // Jezeli klucz jest mniejszy, wywolanie funkcje w lewym poddrzewie
        node->left = insert(node->left, key, value, inserted);
    } else if (key > node->entry.key) { // Jezeli klucz jest wiekszy, wywowywolanielaj funkcje w prawm poddrzewie
        node->right = insert(node->right, key, value, inserted);
    } else { // Przypadek w ktorym klucz jest taki sam
        node->entry.value = value; // Aktualizacja wartosci
        inserted = false;
    }
    return balance(node); // Balansowanie drzewa po wstawieniu
}

// Rekurencyjna metoda usuwania
BSTNode* BalancedBST::remove(BSTNode* node, uint32_t key, bool &removed) {
    if (node == nullptr) { // Jezeli obecny wezel nie istnieje, zwraca null
        return node;
    }
    if (key < node->entry.key) { // Jezeli klucz jest mniejszy, wywolanie funkcje w lewym poddrzewie
        node->left = remove(node->left, key, removed);
    } else if (key > node->entry.key) { // Jezeli klucz jest wiekszy, wywolanie funkcje w prawym poddrzewie
        node->right = remove(node->right, key, removed);
    } else { // Jezeli klucz jest rowny, usuniecie wezla i reorganizacja drzewa
        removed = true;
        if (node->left == nullptr) {
            BSTNode* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            BSTNode* temp = node->left;
            delete node;
            return temp;
        }
        BSTNode* temp = findMin(node->right);
        node->entry.key = temp->entry.key;
        node->entry.value = temp->entry.value;
        node->right = remove(node->right, temp->entry.key, removed);
    }
    return balance(node); // Balansowanie drzewa po usunięciu
}

// Rekurencyjna metoda wyszukiwania
uint32_t BalancedBST::search(BSTNode* node, uint32_t key) const {
    if (node == nullptr) {
        throw std::runtime_error("Nie znaleziono elementu.");
    }
    if (key < node->entry.key) { // Jezeli klucz jest mniejszy, szukanie w lewym poddrzewie
        return search(node->left, key);
    } else if (key > node->entry.key) { // Jezeli klucz jest wiekszy, szukanie w prawym poddrzewie
        return search(node->right, key);
    } else {
        return node->entry.value;
    }
}

// Rekurencyjne usuwanie wezlow poddrzew
void BalancedBST::destroyTree(BSTNode* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

// Rekurencyjna metoda kopiowania drzew
BSTNode* BalancedBST::copyTree(BSTNode* node) {
    if (node == nullptr) {
        return nullptr;
    }
    BSTNode* newNode = new BSTNode(node->entry.key, node->entry.value);
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);
    return newNode;
}

// Rekurencyjna metoda wyswietlania elementow
void BalancedBST::print(BSTNode* node) const {
    if (node != nullptr) {
        print(node->left);
        std::cout << "(" << node->entry.key << ", " << node->entry.value << ") " << std::endl;
        print(node->right);
    }
}

// Metoda znajdujaca wezel z minimalnum kluczem
BSTNode* BalancedBST::findMin(BSTNode* node) const {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// Funkcje pomocnicze dla AVL
int BalancedBST::height(BSTNode* node) const {
    return node == nullptr ? 0 : node->height;
}

int BalancedBST::balanceFactor(BSTNode* node) const {
    return node == nullptr ? 0 : height(node->left) - height(node->right);
}

BSTNode* BalancedBST::rotateLeft(BSTNode* node) {
    BSTNode* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    node->height = std::max(height(node->left), height(node->right)) + 1;
    newRoot->height = std::max(height(newRoot->left), height(newRoot->right)) + 1;
    return newRoot;
}

BSTNode* BalancedBST::rotateRight(BSTNode* node) {
    BSTNode* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    node->height = std::max(height(node->left), height(node->right)) + 1;
    newRoot->height = std::max(height(newRoot->left), height(newRoot->right)) + 1;
    return newRoot;
}

BSTNode* BalancedBST::balance(BSTNode* node) {
    node->height = std::max(height(node->left), height(node->right)) + 1;
    int balance = balanceFactor(node);

    if (balance > 1) {
        if (balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }
    if (balance < -1) {
        if (balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }
    return node;
}