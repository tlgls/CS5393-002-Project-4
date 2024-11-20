// QueryProcessor.h
#pragma once
#include "IndexHandler.h"
#include <string>
#include <vector>

class QueryProcessor {
private:
    IndexHandler &indexHandler;

public:
    QueryProcessor(IndexHandler &handler) : indexHandler(handler) {}
    std::vector<std::string> executeQuery(const std::string &query);
};
