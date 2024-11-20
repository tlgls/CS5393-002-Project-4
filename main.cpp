#include <iostream>
#include <dirent.h>   // for opendir, readdir, closedir
#include <cstring>    // for strerror
#include <vector>
#include <string>
#include <cstdlib>    // for std::getline

#include "DocumentParser.h"
#include "IndexHandler.h"
#include "QueryProcessor.h"

int main() {
    DocumentParser parser("stopwords.txt");
    IndexHandler indexHandler;
    QueryProcessor queryProcessor(indexHandler);

    std::cout << "Welcome to SuperSearch!\n";
    while (true) {
        std::cout << "\nOptions:\n";
        std::cout << "1. Index documents\n";
        std::cout << "2. Load indices from file\n";
        std::cout << "3. Save indices to file\n";
        std::cout << "4. Query\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore(); // Ignore newline

        if (choice == 1) {
            std::string directory;
            std::cout << "Enter directory path: ";
            std::getline(std::cin, directory);

            DIR* dir = opendir(directory.c_str());  // Open directory
            if (!dir) {
                std::cerr << "Error opening directory: " << strerror(errno) << std::endl;
                continue;
            }

            struct dirent* entry;
            while ((entry = readdir(dir)) != nullptr) {
                // Skip "." and ".." directories
                if (std::string(entry->d_name) == "." || std::string(entry->d_name) == "..")
                    continue;

                std::string filePath = directory + "/" + entry->d_name;
                std::string title, text;
                std::vector<std::string> orgs, persons;
                parser.parseJSON(filePath, title, text, orgs, persons);
                indexHandler.indexDocument(entry->d_name, title, text, orgs, persons);
            }

            closedir(dir);  // Close directory
        } else if (choice == 2) {
            indexHandler.loadIndices("terms.idx", "orgs.idx", "persons.idx");
        } else if (choice == 3) {
            indexHandler.saveIndices("terms.idx", "orgs.idx", "persons.idx");
        } else if (choice == 4) {
            std::string query;
            std::cout << "Enter query: ";
            std::getline(std::cin, query);
            auto results = queryProcessor.executeQuery(query);
            for (const auto &res : results)
                std::cout << res << std::endl;
        } else if (choice == 5) {
            break;
        }
    }

    return 0;
}
