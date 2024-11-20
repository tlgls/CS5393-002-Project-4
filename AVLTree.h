// AVLTree.h
#pragma once
#include <string>
#include <vector>
#include <fstream>

class AVLTree {
private:
    struct Node {
        std::string key;                // Term or Entity
        std::vector<std::string> docs; // List of document IDs
        Node *left, *right;
        int height;
        Node(const std::string &k) : key(k), left(nullptr), right(nullptr), height(1) {}
    };

    Node *root;

    int height(Node *n) { return n ? n->height : 0; }

    Node *rotateRight(Node *y);
    Node *rotateLeft(Node *x);
    Node *insert(Node *node, const std::string &key, const std::string &docID);
    void serialize(Node *node, std::ofstream &out);
    Node *deserialize(std::ifstream &in);

public:
    AVLTree() : root(nullptr) {}
    void insert(const std::string &key, const std::string &docID);
    void saveToFile(const std::string &filename);
    void loadFromFile(const std::string &filename);
};
