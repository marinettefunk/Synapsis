/*
 * Copyright (c) 2024 Marinette Funk. All rights reserved.
 *
 * This file is part of the SYNAPSIS Project.
 *
 * Description: Virtual Assistant to help with file organisation, with ChatBot NLP functionality.
 *
 * Unauthorized copying of this file, via any medium, is strictly prohibited.
 * Proprietary and confidential.
 *
 * For inquiries, contact: marinettefunk@gmail.com
 */

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "formatting.h"
#include "profile.h"
#include "files.h"
#include "welcome.h"
#include "chat.h"

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

// Input validation when choosing option from Main Menu.
int choice() {
    int choice;
    std::cout << ">>>>>> Enter your choice: ";
    std::cin >> choice;

    while (std::cin.fail() || choice < 1 || choice > 4) {
        if (std::cin.fail()) {
            std::cerr << "Error: Invalid input. Please enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            std::cerr << "Error: Invalid choice. Please enter a number between 1 and 4." << std::endl;
        }
        std::cout << ">>>>>> Enter your choice: ";
        std::cin >> choice;
    }

    return choice;
}

// Function to print Main Menu.
void printMenu (const std::string& name) {
    system(CLEAR_COMMAND);
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
            std::cout << "Invalid input. Please enter a number between 1 and 4." << std::endl;
            break;
    }
}