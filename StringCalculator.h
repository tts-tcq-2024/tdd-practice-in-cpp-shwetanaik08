#ifndef STRINGCALCULATOR_H
#define STRINGCALCULATOR_H

#include <string>
#include <vector>

#include <gtest/gtest.h>
class StringCalculator {
public:
    int add(const std::string& numbers);

private:
    // Helper functions
    std::vector<std::string> split(const std::string& str, const std::string& delimiter);
    int toInt(const std::string& str);
};

#endif // STRINGCALCULATOR_H
