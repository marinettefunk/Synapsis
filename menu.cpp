#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "formatting.h"
#include "errors.h"
#include "profile.h"
#include "files.h"

int choice() {
    int choice;
    std::cout << ">>>>>> Enter your choice: ";
    std::cin >> choice;

    while (std::cin.fail() || choice < 1 || choice > 3) {
        inputError("Invalid input. Please enter a number between 1 and 3.");
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
    std::cout << "4. Chat Bot" << std::endl;
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
            // Add functionality for Exit here
            break;
    }
}