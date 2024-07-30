#include "StringCalculator.h"
#include <sstream>
#include <stdexcept>
#include <regex>
#include <numeric>
#include <vector>

int StringCalculator::add(const std::string& numbers) {
    if (numbers.empty()) {
        return 0;
    }

    std::string delimiters = ",|\n";
    std::string nums = numbers;

    nums = getDelimitersAndNumbers(numbers, delimiters);

    return calculateSum(nums, delimiters);
}

int StringCalculator::calculateSum(const std::string& numbers, const std::string& delimiters) {
    std::vector<int> nums = splitAndParseNumbers(numbers, delimiters);
    std::vector<int> negatives = filterNegativeNumbers(nums);

    if (!negatives.empty()) {
        throwNegativeNumbersException(negatives);
    }

    return std::accumulate(nums.begin(), nums.end(), 0);
}

std::vector<int> StringCalculator::splitAndParseNumbers(const std::string& numbers, const std::string& delimiters) {
    std::regex delimiterPattern(delimiters);
    std::sregex_token_iterator iter(numbers.begin(), numbers.end(), delimiterPattern, -1);
    std::sregex_token_iterator end;

    std::vector<int> nums;
    for (; iter != end; ++iter) {
        if (!iter->str().empty()) { // Skip empty tokens
            nums.push_back(parseNumber(*iter));
        }
    }

    return nums;
}

std::vector<int> StringCalculator::filterNegativeNumbers(const std::vector<int>& nums) {
    std::vector<int> negatives;
    for (int num : nums) {
        if (num < 0) {
            negatives.push_back(num);
        }
    }
    return negatives;
}

int StringCalculator::parseNumber(const std::string& numStr) {
    int num = std::stoi(numStr);
    return num > 1000 ? 0 : num;
}

void StringCalculator::throwNegativeNumbersException(const std::vector<int>& negatives) {
    std::ostringstream oss;
    oss << "negatives not allowed: ";
    for (size_t i = 0; i < negatives.size(); ++i) {
        if (i > 0) {
            oss << ", ";
        }
        oss << negatives[i];
    }
    throw std::runtime_error(oss.str());
}

std::string StringCalculator::regex_escape(const std::string& str) {
    static const std::regex re(R"([.^$|()\[\]{}*+?\\])");
    return std::regex_replace(str, re, R"(\$&)");
}

std::string StringCalculator::extractDelimiters(const std::string& delimiterSection) {
    std::string delimiters;
    if (delimiterSection[0] == '[') {
        std::regex re("\\[(.*?)\\]");
        std::sregex_iterator iter(delimiterSection.begin(), delimiterSection.end(), re);
        std::sregex_iterator end;
        while (iter != end) {
            delimiters += "|" + regex_escape((*iter)[1].str());
            ++iter;
        }
    } else {
        delimiters = regex_escape(delimiterSection);
    }
    return delimiters;
}

std::string StringCalculator::getDelimitersAndNumbers(const std::string& numbers, std::string& delimiters) {
    if (numbers.substr(0, 2) == "//") {
        size_t newlinePos = numbers.find('\n');
        std::string delimiterSection = numbers.substr(2, newlinePos - 2);
        delimiters = extractDelimiters(delimiterSection);
        return numbers.substr(newlinePos + 1);
    }
    return numbers;
}
