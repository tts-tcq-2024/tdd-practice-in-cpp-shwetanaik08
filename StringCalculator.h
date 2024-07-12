#ifndef STRINGCALCULATOR_H
#define STRINGCALCULATOR_H

#include <string>
#include <vector>

class StringCalculator {
public:
    int add(const std::string& numbers);

private:
    std::vector<std::string> split(const std::string& str, const std::string& delimiter);
    int toInt(const std::string& str);
    std::string getDelimiter(const std::string& numbers, std::string& numbersWithoutDelimiter);
    void replaceNewlinesWithDelimiter(std::string& numbersWithoutDelimiter, const std::string& delimiter);
    std::vector<int> processNumbers(const std::vector<std::string>& tokens);
};

#endif // STRINGCALCULATOR_H
