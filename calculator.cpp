#include <iostream>
#include <string>
#include "welcome.h"
#include "formatting.h"

#ifdef _WIN32
#define CLEAR_COMMAND "cls" // Windows
#else
#define CLEAR_COMMAND "clear" // Unix/Linux, macOS
#endif

void calculatorMenu(){
std::cout << "1. Addition" << std::endl;
std::cout << "2. Subtraction" << std::endl;
std::cout << "3. Multiplication" << std::endl;
std::cout << "4. Division" << std::endl;
std::cout << "5. History" << std::endl;
std::cout << "6. Back to Main Menu" << std::endl;
std::cout << std::endl;
}

void calculator(){
    system(CLEAR_COMMAND); // Clear the screen after profile creation
    dateTime();
    printLogo();
    std::cout << std::endl;
    printBorder("CALCULATOR");
    calculatorMenu();
}

