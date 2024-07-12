#ifndef STRING_CALCULATOR_H
#define STRING_CALCULATOR_H

#include <string>
#include <vector>

class StringCalculator {
public:
    int add(const std::string& numbers);

private:
    std::vector<std::string> split(const std::string& str, const std::string& delimiter);
    int toInt(const std::string& str);
    std::vector<int> processNumbers(const std::vector<std::string>& tokens);
};

#endif // STRING_CALCULATOR_H
