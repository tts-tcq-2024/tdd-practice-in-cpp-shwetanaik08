#include "StringCalculator.h"
#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <numeric>

// Helper function to split a string by a delimiter
std::vector<std::string> StringCalculator::split(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do {
        pos = str.find(delimiter, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos - prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delimiter.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

// Helper function to convert a string to an integer
int StringCalculator::toInt(const std::string& str) {
    return std::stoi(str);
}

// Validate and process numbers
std::vector<int> StringCalculator::processNumbers(const std::vector<std::string>& tokens) {
    std::vector<int> values;
    std::vector<int> negatives;

    for (const auto& token : tokens) {
        int value = toInt(token);
        if (value < 0) {
            negatives.push_back(value);
        } else if (value <= 1000) {
            values.push_back(value);
        }
    }

    if (!negatives.empty()) {
        std::string errorMsg = "Negatives not allowed: ";
        for (const auto& neg : negatives) {
            errorMsg += std::to_string(neg) + " ";
        }
        throw std::runtime_error(errorMsg);
    }

    return values;
}

int StringCalculator::add(const std::string& numbers) {
    if (numbers.empty()) return 0;

    std::string delimiter = ",";
    std::string numbersWithoutDelimiter = numbers;

    if (numbers.find("//") == 0) {
        size_t delimiterPos = numbers.find('\n');
        delimiter = numbers.substr(2, delimiterPos - 2);
        numbersWithoutDelimiter = numbers.substr(delimiterPos + 1);
    }

    // Replace newline characters with delimiter
    std::replace(numbersWithoutDelimiter.begin(), numbersWithoutDelimiter.end(), '\n', delimiter[0]);

    std::vector<std::string> tokens = split(numbersWithoutDelimiter, delimiter);
    std::vector<int> values = processNumbers(tokens);

    return std::accumulate(values.begin(), values.end(), 0);
}
