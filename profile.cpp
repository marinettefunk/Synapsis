#include <iostream>
#include <string>
#include <fstream>
#include <limits> // Required for numeric_limits
#include "formatting.h"
#include "welcome.h"
#include "menu.h"
#include "errors.h"

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

// Function to save user data to a file.
void saveUserData(const std::string& name, const std::string& password) {
    std::ofstream file("user_data.txt");
    if (file.is_open()) {
        file << name << std::endl;
        file << password << std::endl;
        file.close();
    } else {
        inputError("Error: Unable to open file for saving user data.");
    }
}

// Function to load user data from a file.
void loadUserData(std::string& name, std::string& password) {
    std::ifstream file("user_data.txt");
    if (file.is_open()) {
        std::getline(file, name);
        std::getline(file, password);
        file.close();
    } else {
        inputError("Error: Unable to open file to load user data. Starting with blank profile.");
        name = "";
        password = "";
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
            inputError("Invalid input. Please enter 'y' or 'n'.");
        }
    }
}

// Function to get and confirm the user's password.
std::string getPassword() {
    std::string password, confirmPassword;
    std::cout << ">>>>> Please enter your password: ";
    std::getline(std::cin, password);

    while (true) {
        std::cout << ">>>>> Re-enter your password: ";
        std::getline(std::cin, confirmPassword);

        if (confirmPassword == password) {
            break;
        } else {
            inputError("Passwords do not match. Please try again.");
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
        inputError("Failed to clear the screen.");
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
                inputError("Incorrect password. Please try again.");
            }
        }

        if (system(CLEAR_COMMAND) != 0) {
            inputError("Failed to clear the screen.");
        }
    }

    return name;
}

// Function to display the Profile Settings Menu.
void printProfileSettingsMenu() {
    if (system(CLEAR_COMMAND) != 0) {
        inputError("Failed to clear the screen.");
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

// Utility function to pause and wait for user input before returning to the menu.
void pauseForReturn() {
    std::cout << "\n>>>>> Press Enter to return to the menu <<<<<<";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Function to display the user's profile.
void viewProfile(const std::string& name, const std::string& password) {
    if (system(CLEAR_COMMAND) != 0) {
        inputError("Failed to clear the screen.");
    }
    printBorder("VIEW PROFILE");
    std::cout << "Name: " << name << std::endl;
    std::cout << "Password: " << std::string(password.length(), '*') << std::endl;
    pauseForReturn();
}

// Function to change the user's name.
void changeName(std::string& name) {
    if (system(CLEAR_COMMAND) != 0) {
        inputError("Failed to clear the screen.");
    }
    printBorder("CHANGE NAME");

    std::cout << "Your name is currently " << name << ". Are you sure you want to change your name? (y/n): ";
    char confirm;
    std::cin >> confirm;
    std::cin.ignore();

    if (confirm == 'y' || confirm == 'Y') {
        std::cout << ">>>>> Please enter your new name: ";
        std::getline(std::cin, name);
        std::string password = getPassword();
        saveUserData(name, password);
        std::cout << "Name updated successfully to " << name << "!" << std::endl;
    } else if (confirm == 'n' || confirm == 'N') {
        std::cout << "Name change cancelled." << std::endl;
    } else {
        inputError("Invalid input. Please enter 'y' or 'n'.");
    }
    pauseForReturn();
}

// Function to change the user's password.
void changePassword(std::string& password) {
    if (system(CLEAR_COMMAND) != 0) {
        inputError("Failed to clear the screen.");
    }
    printBorder("CHANGE PASSWORD");

    std::cout << "Are you sure you want to change your password? (y/n): ";
    char confirm;
    std::cin >> confirm;
    std::cin.ignore();

    if (confirm == 'y' || confirm == 'Y') {
        password = getPassword();
        std::string name = getName();
        saveUserData(name, password);
        std::cout << "Password updated successfully!" << std::endl;
    } else if (confirm == 'n' || confirm == 'N') {
        std::cout << "Password change cancelled." << std::endl;
    } else {
        inputError("Invalid input. Please enter 'y' or 'n'.");
    }
    pauseForReturn();
}

// Function to delete the user's profile.
void deleteProfile(std::string& name, std::string& password) {
    if (system(CLEAR_COMMAND) != 0) {
        inputError("Failed to clear the screen.");
    }
    printBorder("DELETE PROFILE");

    std::cout << "Are you sure you want to delete your profile? (y/n): ";
    char confirm;
    std::cin >> confirm;
    std::cin.ignore();

    if (confirm == 'y' || confirm == 'Y') {
        name.clear();
        password.clear();
        saveUserData(name, password);
        std::cout << "Profile deletion successful." << std::endl;
    } else if (confirm == 'n' || confirm == 'N') {
        std::cout << "Profile deletion cancelled." << std::endl;
    } else {
        inputError("Invalid input. Please enter 'y' or 'n'.");
    }
    pauseForReturn();
}

// Main function to handle profile settings menu.
void profileSettings(std::string& name, std::string& password) {
    int choice;
    do {
        printProfileSettingsMenu();
        std::cout << ">>>>> Please select an option: ";
        if (!(std::cin >> choice) || choice < 1 || choice > 5) {
            inputError("Invalid input. Please enter a number between 1 and 5.");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                viewProfile(name, password);
                break;
            case 2:
                changeName(name);
                break;
            case 3:
                changePassword(password);
                break;
            case 4:
                deleteProfile(name, password);
                break;
            case 5:
                std::cout << "Returning to the Main Menu..." << std::endl;
                break;
        }
    } while (choice != 5);
}

