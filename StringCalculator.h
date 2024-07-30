#ifndef STRINGCALCULATOR_H
#define STRINGCALCULATOR_H

#include <string>
#include <vector>

class StringCalculator {
public:
    int add(const std::string& numbers);

private:
    int calculateSum(const std::string& numbers, const std::string& delimiters);
    std::vector<int> splitAndParseNumbers(const std::string& numbers, const std::string& delimiters);
    std::vector<int> filterNegativeNumbers(const std::vector<int>& nums);
    int parseNumber(const std::string& numStr);
    void throwNegativeNumbersException(const std::vector<int>& negatives);
    std::string regex_escape(const std::string& str);
    std::string extractDelimiters(const std::string& delimiterSection);
    std::string getDelimitersAndNumbers(const std::string& numbers, std::string& delimiters);
};

#endif // STRINGCALCULATOR_H
