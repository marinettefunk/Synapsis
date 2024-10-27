#include <iostream>
#include <string>
#include <limits> // Required for numeric_limits

void inputError(const std::string& message) {
    if (std::cin.fail()) { 
        std::cout << message << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}