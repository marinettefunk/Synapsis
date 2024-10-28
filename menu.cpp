#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "formatting.h"
#include "errors.h"
#include "profile.h"
#include "files.h"
#include "notes.h"
#include "calculator.h"

int choice() {
    int choice;
    std::cout << ">>>>>> Enter your choice: ";
    std::cin >> choice;

    while (std::cin.fail() || choice < 1 || choice > 5) {
        inputError("Invalid input. Please enter a number between 1 and 5.");
        std::cout << ">>>>>> Enter your choice: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> choice;
    }

    return choice;
}

void printMenu() {
    printBorder("MENU");
    std::cout << "1. Profile Settings" << std::endl;
    std::cout << "2. File Organiser" << std::endl;
    std::cout << "3. Calculator" << std::endl;
    std::cout << "4. Notes App" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << std::endl;

    int selectedChoice = choice();

    switch (selectedChoice) {
        case 1: {
            std::string name, password;
            loadUserData(name, password);
            profileSettings(name, password);
            break;
        }
        case 2:
            printFileOrganiser();
            break;
        case 3:
            calculator();
            break;
        case 4:
            // Add functionality for notes here
            break;
        case 5:
            // Add functionality for Exit here
            break;
    }
}