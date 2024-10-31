#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "formatting.h"
#include "errors.h"
#include "profile.h"
#include "files.h"
#include "welcome.h"
#include "chat.h"

int choice() {
    int choice;
    std::cout << ">>>>>> Enter your choice: ";
    std::cin >> choice;

    while (std::cin.fail() || choice < 1 || choice > 5) {
        inputError("Invalid input. Please enter a number between 1 and 5.");
        std::cout << ">>>>>> Enter your choice: ";
        std::cin >> choice;
    }

    return choice;
}
void printMenu (const std::string& name) {

    dateTime();
    printLogo();
    std::cout << std::endl;
    std::cout << "Hello, " << name << "! What can I help you with today?" << std::endl;
    std::cout << std::endl;

    printBorder("MENU");
    std::cout << "1. Profile Settings" << std::endl;
    std::cout << "2. File Organiser App" << std::endl;
    std::cout << "3. ChatBot" << std::endl;
    std::cout << "4. Exit" << std::endl;
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
            fileOrganiserApp();
            break;
        case 3:
            ChatBot ();
            break;
        case 4:
            std::cout << "Thank you for using SYNAPSIS! Exiting program..." << std::endl;
            exit(0);
            break;           
        default:
            std::cout << "Invalid choice." << std::endl;
            break;
    }
}