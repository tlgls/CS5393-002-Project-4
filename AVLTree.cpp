#include "AVLTree.h"
#include <iostream>
#include <fstream>

int getHeight(AVLTree::Node *node) {
    return node ? node->height : 0;
}

AVLTree::Node *AVLTree::rotateRight(AVLTree::Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

AVLTree::Node *AVLTree::rotateLeft(AVLTree::Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

AVLTree::Node *AVLTree::insert(AVLTree::Node *node, const std::string &key, const std::string &docID) {
    if (!node) return new Node(key);

    if (key < node->key) {
        node->left = insert(node->left, key, docID);
    } else if (key > node->key) {
        node->right = insert(node->right, key, docID);
    } else {
        node->docs.push_back(docID); // If the key already exists, add the document to the list
        return node;
    }

    // Update height of this node
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    // Balance the node
    int balance = getHeight(node->left) - getHeight(node->right);

    // Left Left case
    if (balance > 1 && key < node->left->key) return rotateRight(node);

    // Right Right case
    if (balance < -1 && key > node->right->key) return rotateLeft(node);

    // Left Right case
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left case
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void AVLTree::insert(const std::string &key, const std::string &docID) {
    root = insert(root, key, docID);
}

void AVLTree::saveToFile(const std::string &filename) {
    std::ofstream file(filename);
    serialize(root, file);
}

void AVLTree::serialize(AVLTree::Node *node, std::ofstream &out) {
    if (!node) {
        out << "null\n";
        return;
    }
    out << node->key << "\n";
    out << node->docs.size() << "\n";
    for (const auto &doc : node->docs) {
        out << doc << "\n";
    }
    serialize(node->left, out);
    serialize(node->right, out);
}

void AVLTree::loadFromFile(const std::string &filename) {
    std::ifstream file(filename);
    root = deserialize(file);
}

AVLTree::Node *AVLTree::deserialize(std::ifstream &in) {
    std::string key;
    if (!(in >> key) || key == "null") return nullptr;

    Node *node = new Node(key);
    size_t docCount;
    in >> docCount;
    node->docs.resize(docCount);
    for (size_t i = 0; i < docCount; ++i) {
        in >> node->docs[i];
    }

    node->left = deserialize(in);
    node->right = deserialize(in);
    return node;
}
