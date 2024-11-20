#include "DocumentParser.h"
#include <fstream>
#include <sstream>
#include <iostream>

DocumentParser::DocumentParser(const std::string &stopwordFile) {
    // Load stopwords from the file
    std::ifstream file(stopwordFile);
    std::string word;
    while (file >> word) {
        stopwords.insert(word);
    }
}

std::string DocumentParser::stem(const std::string &word) {
    // Simple stub for stemming function; replace with real stemming logic
    return word;
}

std::vector<std::string> DocumentParser::parseText(const std::string &text) {
    std::vector<std::string> words;
    std::istringstream stream(text);
    std::string word;
    while (stream >> word) {
        word = stem(word); // Optionally stem the word
        if (stopwords.find(word) == stopwords.end()) { // Ignore stopwords
            words.push_back(word);
        }
    }
    return words;
}

void DocumentParser::parseJSON(const std::string &filename, std::string &title, std::string &text, std::vector<std::string> &organizations, std::vector<std::string> &persons) {
    title = "Example Title"; // This should come from the JSON parsing logic
    text = "Example text from the document..."; // Extract from JSON text field
    organizations = {"Org1", "Org2"}; // Extract organizations
    persons = {"Person1", "Person2"}; // Extract persons
}
