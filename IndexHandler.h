// IndexHandler.h
#pragma once
#include "AVLTree.h"
#include "DocumentParser.h"
#include <string>

class IndexHandler {
private:
    AVLTree termIndex;
    AVLTree orgIndex;
    AVLTree personIndex;

public:
    void indexDocument(const std::string &docID, const std::string &title, const std::string &text,
                       const std::vector<std::string> &organizations, const std::vector<std::string> &persons);
    void saveIndices(const std::string &termFile, const std::string &orgFile, const std::string &personFile);
    void loadIndices(const std::string &termFile, const std::string &orgFile, const std::string &personFile);
};
