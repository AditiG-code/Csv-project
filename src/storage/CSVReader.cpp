#include "CSVReader.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

CSVReader::CSVReader(const std::string& filePath)
    : filePath(filePath) {}

void CSVReader::read() {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open CSV file: " + filePath);
    }

    std::string line;

    // Read header line
    if (std::getline(file, line)) {
        headers = split(line, ',');
    }

    // Read data rows
    while (std::getline(file, line)) {
        std::vector<std::string> row = split(line, ',');
        if (!row.empty()) {
            rows.push_back(row);
        }
    }

    file.close();
}

std::vector<std::string> CSVReader::split(const std::string& line, char delimiter) const {
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(line);

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

const std::vector<std::string>& CSVReader::getHeaders() const {
    return headers;
}

const std::vector<std::vector<std::string>>& CSVReader::getRows() const {
    return rows;
}
