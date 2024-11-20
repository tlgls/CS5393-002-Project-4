// DocumentParser.h
#pragma once
#include <string>
#include <vector>
#include <unordered_set>
// #include "rapidjson/document.h"

class DocumentParser {
private:
    std::unordered_set<std::string> stopwords;
    std::string stem(const std::string &word);

public:
    DocumentParser(const std::string &stopwordFile);
    std::vector<std::string> parseText(const std::string &text);
    void parseJSON(const std::string &filename, std::string &title, std::string &text,
                   std::vector<std::string> &organizations, std::vector<std::string> &persons);
};
