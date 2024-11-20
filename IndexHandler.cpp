#include "IndexHandler.h"
#include <iostream>

void IndexHandler::indexDocument(const std::string &docID, const std::string &title, const std::string &text,
                                  const std::vector<std::string> &organizations, const std::vector<std::string> &persons) {
    // Index terms from the document
    std::vector<std::string> words = DocumentParser::parseText(text);
    for (const auto &word : words) {
        termIndex.insert(word, docID);
    }
    
    // Index organizations and persons
    for (const auto &org : organizations) {
        orgIndex.insert(org, docID);
    }
    for (const auto &person : persons) {
        personIndex.insert(person, docID);
    }
}

void IndexHandler::saveIndices(const std::string &termFile, const std::string &orgFile, const std::string &personFile) {
    termIndex.saveToFile(termFile);
    orgIndex.saveToFile(orgFile);
    personIndex.saveToFile(personFile);
}

void IndexHandler::loadIndices(const std::string &termFile, const std::string &orgFile, const std::string &personFile) {
    termIndex.loadFromFile(termFile);
    orgIndex.loadFromFile(orgFile);
    personIndex.loadFromFile(personFile);
}
