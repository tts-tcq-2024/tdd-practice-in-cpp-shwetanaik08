#include "StringCalculator.h"
#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <numeric>

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

int StringCalculator::toInt(const std::string& str) {
    return std::stoi(str);
}

int StringCalculator::add(const std::string& numbers) {
    if (numbers.empty()) {
        return 0;
    }

    std::string delimiter = ",";
    std::string numbersWithoutDelimiter = numbers;

    if (numbers.find("//") == 0) {
        size_t delimiterPos = numbers.find('\n');
        delimiter = numbers.substr(2, delimiterPos - 2);
        numbersWithoutDelimiter = numbers.substr(delimiterPos + 1);
    }

    std::replace(numbersWithoutDelimiter.begin(), numbersWithoutDelimiter.end(), '\n', delimiter[0]);
    std::vector<std::string> tokens = split(numbersWithoutDelimiter, delimiter);
    
    return std::accumulate(processNumbers(tokens).begin(), processNumbers(tokens).end(), 0);
}

std::vector<int> StringCalculator::processNumbers(const std::vector<std::string>& tokens) {
    std::vector<int> values;
    for (const auto& token : tokens) {
        validateAndAdd(token, values);
    }
    return values;
}

void StringCalculator::validateAndAdd(const std::string& token, std::vector<int>& values) {
    int value = toInt(token);
    if (value < 0) {
        throw std::runtime_error("Negative numbers are not allowed: " + token);
    }
    if (value <= 1000) {
        values.push_back(value);
    }
}
