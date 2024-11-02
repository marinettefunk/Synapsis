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
#include <string>
#include <fstream>
#include <limits>
#include "formatting.h"
#include "welcome.h"
#include "menu.h"

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

// Function to save user data to a file.
void saveUserData(const std::string& name, const std::string& password) {
    std::ofstream file("user_data.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file for saving user data." << std::endl;
        return;
    }

    file << name << std::endl;
    file << password << std::endl;
    file.close();

    if (!file.good()) {
        std::cerr << "Error: Unable to write to file." << std::endl;
    }
}

// Function to load user data from a file.
void loadUserData(std::string& name, std::string& password) {
    std::ifstream file("user_data.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file to load user data. Starting with blank profile." << std::endl;
        name = "";
        password = "";
        return;
    }

    std::getline(file, name);
    std::getline(file, password);
    file.close();

    if (!file.good()) {
        std::cerr << "Error: Unable to read from file." << std::endl;
    }
}

// Function to get the user's name.
std::string getName() {
    std::string name;
    std::cout << ">>>>> Please enter your name: ";
    std::getline(std::cin, name);
    return name;
}

// Function to confirm the user's name.
void nameConfirmation(std::string& name) {
    char confirm;
    while (true) {
        std::cout << ">>>>> Your name is " << name << ". Is this correct? (y/n): ";
        std::cin >> confirm;
        std::cin.ignore();

        if (confirm == 'y' || confirm == 'Y') {
            break;
        } else if (confirm == 'n' || confirm == 'N') {
            name = getName();
        } else {
            std::cerr << "Invalid input. Please enter 'y' or 'n'." << std::endl;
        }
    }
}

// Function to get and confirm the user's password.
std::string getPassword() {
    std::string password, confirmPassword;
    std::cout << ">>>>> Please enter your password: ";
    std::getline(std::cin, password);

    while (true) {
        std::cout << ">>>>> Re-enter your password: "; // Password needs to be confirmed.
        std::getline(std::cin, confirmPassword);

        if (confirmPassword == password) {
            break;
        } else {
            std::cerr << "Passwords do not match. Please try again." << std::endl;
        }
    }

    return password;
}

// Function to create a profile when program is first run.
void createProfile(std::string& name, std::string& password) {
    printBorder("FIRST, LET'S CREATE YOUR PROFILE");

    name = getName();
    nameConfirmation(name);

    password = getPassword();
    saveUserData(name, password);

    std::cout << "Profile created successfully!" << std::endl;
    if (system(CLEAR_COMMAND) != 0) {
        std::cerr << "Error: Failed to clear the screen." << std::endl;
    }

    printMenu(name);
}

// Function on program start based on user data.
std::string runProgram() {
    std::string name, password;
    loadUserData(name, password);

    if (name.empty() || password.empty()) {
        createProfile(name, password);
    } else {
        std::cout << "Welcome back, " + name + "!" << std::endl;
        std::string inputPassword;
        bool loginSuccessful = false;

        while (!loginSuccessful) {
            std::cout << ">>>>> Please enter your password: ";
            std::getline(std::cin, inputPassword);

            if (inputPassword == password) {
                loginSuccessful = true;
            } else {
                std::cerr << "Incorrect password. Please try again." << std::endl;
            }
        }

        if (system(CLEAR_COMMAND) != 0) {
            std::cerr << "Error: Failed to clear the screen." << std::endl;
        }
    }

    return name;
}

// Function to display the Profile Settings Menu.
void printProfileSettingsMenu() {
    if (system(CLEAR_COMMAND) != 0) {
        std::cerr << "Error: Failed to clear the screen." << std::endl;
    }
    dateTime();
    printLogo();
    std::cout << std::endl;
    printBorder("PROFILE SETTINGS");
    std::cout << "1. View Profile" << std::endl;
    std::cout << "2. Change Name" << std::endl;
    std::cout << "3. Change Password" << std::endl;
    std::cout << "4. Delete Profile" << std::endl;
    std::cout << "5. Back to Main Menu" << std::endl;
    std::cout << std::endl;
}

// Function to display the user's profile.
void viewProfile(const std::string& name, const std::string& password) {
    if (system(CLEAR_COMMAND) != 0) {
        std::cerr << "Error: Failed to clear the screen." << std::endl;
    }
    printBorder("VIEW PROFILE");
    std::cout << "Name: " << name << std::endl;
    std::cout << "Password: " << std::string(password.length(), '*') << std::endl;
    pauseForReturn();
}

// Function to change the name of the user.
void changeName(std::string& name, std::string& password) {
    if (system(CLEAR_COMMAND) != 0) {
        std::cerr << "Error: Failed to clear the screen." << std::endl;
    }
    printBorder("CHANGE NAME");

    char confirm;
    while (true) {
        std::cout << "Your name is currently " << name << "." << std::endl;
        std::cout << ">>>>> Are you sure you want to change your name? (y/n): ";
        std::cin >> confirm;
        std::cin.ignore();

        if (confirm == 'y' || confirm == 'Y') {
            std::cout << ">>>>> Please enter your new name: ";
            std::getline(std::cin, name);
            saveUserData(name, password);
            std::cout << "Name updated successfully to " << name << "!" << std::endl;
            break;
        } else if (confirm == 'n' || confirm == 'N') {
            std::cout << "Name change cancelled." << std::endl;
            break;
        } else {
            std::cerr << "Invalid input. Please enter 'y' or 'n'." << std::endl;
        }
    }
    pauseForReturn();
}

// Function to change the user's password.
void changePassword(std::string& password, std::string& name) {
    if (system(CLEAR_COMMAND) != 0) {
        std::cerr << "Error: Failed to clear the screen." << std::endl;
    }
    printBorder("CHANGE PASSWORD");

    std::cout << "Are you sure you want to change your password? (y/n): ";
    char confirm;
    std::cin >> confirm;
    std::cin.ignore();

    if (confirm == 'y' || confirm == 'Y') {
        password = getPassword();
        saveUserData(name, password);
        std::cout << "Password updated successfully!" << std::endl;
    } else if (confirm == 'n' || confirm == 'N') {
        std::cout << "Password change cancelled." << std::endl;
    } else {
        std::cerr << "Invalid input. Please enter 'y' or 'n'." << std::endl;
        changePassword(password, name);
    }
    pauseForReturn();
}

// Function to delete the user's profile.
void deleteProfile(std::string& name, std::string& password) {
    if (system(CLEAR_COMMAND) != 0) {
        std::cerr << "Error: Failed to clear the screen." << std::endl;
    }
    printBorder("DELETE PROFILE");

    char confirm;
    while (true) {
        std::cout << "Are you sure you want to delete your profile? (y/n): ";
        std::cin >> confirm;
        std::cin.ignore();

        if (confirm == 'y' || confirm == 'Y') {
            name.clear();
            password.clear();
            saveUserData(name, password);
            std::cout << "Profile deletion successful." << std::endl;
            system (CLEAR_COMMAND);
            message();
            createProfile(name, password);
            break;
        } else if (confirm == 'n' || confirm == 'N') {
            std::cout << "Profile deletion cancelled." << std::endl;
            break;
        } else {
            std::cerr << "Invalid input. Please enter 'y' or 'n'." << std::endl;
        }
    }
    pauseForReturn();
}

// Main function to handle profile settings menu.
void profileSettings(std::string& name, std::string& password) {
    int choice = 0;

    while (choice != 5) {
        printProfileSettingsMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                viewProfile(name, password);
                break;
            case 2:
                changeName(name, password);
                break;
            case 3:
                changePassword(password, name);
                break;
            case 4:
                deleteProfile(name, password);
                break;
            case 5:
                printMenu(name);
                break;
            default:
                std::cerr << "Invalid choice. Please enter a number between 1 and 5." << std::endl;
                pauseForReturn();
                break;
        }
    }
}