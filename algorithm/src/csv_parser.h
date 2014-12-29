#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

void split(const std::string& s, char delim, std::vector<std::string>* vec) {
    int i = 0;
    int j = s.find(delim);

    while (j != std::string::npos) {
        vec->push_back(s.substr(i, j-i));
        i = j + 1; // Could be ++j but this is clearer I think.
        j++;
        j = s.find(delim, j);

        if (j == std::string::npos) {
            vec->push_back(s.substr(i, s.size()));
        }
    }
}

void parse_csv(std::ifstream* ifs, std::vector<std::string>* data) {
    std::string str;
    std::getline(*ifs, str);
    split(str, ',', data);
}

#endif /* CSV_PARSER_H */
