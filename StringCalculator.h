#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <numeric>

class StringCalculator {
public:
    int add(const std::string& numbers);
private:
    std::vector<std::string> split(const std::string& str, const std::string& delimiter);
    int toInt(const std::string& str);
};
