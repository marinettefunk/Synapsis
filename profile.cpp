#include <iostream>
#include <string>
#include <fstream>
#include <limits> // Required for numeric_limits
#include "formatting.h"
#include "welcome.h"
#include "menu.h"
#include "errors.h"

// Commands to clear the screen for operating system cross-platform compatibility with program.
#ifdef _WIN32
#define CLEAR_COMMAND "cls" // Windows Clear Command.
#else
#define CLEAR_COMMAND "clear" // Unix/Linux and macOS Clear Command.
#endif

// Function to save user data to a file.
void saveUserData(const std::string& name, const std::string& password) {
    std::ofstream file("user_data.txt"); // File is opened in write mode.
    if (file.is_open()) { // If file is open, write to it.
        file << name << std::endl;
        file << password << std::endl;
        file.close(); // File is closed once desired data is writen in.
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
        name = "";
        password = "";
    }
}

// Function to get the user's name.
std::string getName() {
    std::string name;
    std::cout << ">>>>> Please enter your name: ";
    std::getline(std::cin, name);
    inputError("Invalid input. Please enter your name.");
    return name;
}

// Function to confirm the user's name.
void nameConfirmation(std::string& name) {
    char confirm = '\0';
    do {
        std::cout << ">>>>> Your name is " << name << ". Is this correct? (y/n): ";
        std::cin >> confirm;
        inputError("Invalid input. Please enter 'y' or 'n'.");
        if (confirm == 'y' || confirm == 'Y') {
            break;
        } else if (confirm == 'n' || confirm == 'N') {
            getName();
        } else {
            std::cout << "Invalid input. Please enter 'y' or 'n'." << std::endl;
        }
    } while (true);
}

// Function to get and confrim the user's password.
std::string getPassword() {
    std::string password;
    std::string confirmPassword;

    std::cout << ">>>>> Please enter your password: ";
    std::getline(std::cin, password);

    while (true) {
        std::cout << ">>>>> Re-enter your password: ";
        std::getline(std::cin, confirmPassword);

        if (confirmPassword == password) {
            break;
        } else {
            std::cout << "Passwords do not match. Please try again." << std::endl;
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
    system(CLEAR_COMMAND); // Clear the screen after profile creation.

    printMenu(name);
}

// Function on program start based on user data.
std::string runProgram() {
    std::string name;
    std::string password;

    loadUserData(name, password);

    if (name.empty() || password.empty()) { // If the user has not created a profile yet, create one.
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
                std::cout << "Incorrect password. Please try again." << std::endl;
            }
        }

        if (loginSuccessful) {
            system(CLEAR_COMMAND); // Clear the screen after successful login.
        }
    }

    return name;
}

// Function to display the Profile Settings Menu.
void printProfileSettingsMenu() {
    system(CLEAR_COMMAND);
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
    char input;
    while (true) {
        std::cin.get(input);
        if (input == '\n') {
            break;
        } else {
            inputError("Invalid input. Please press Enter to return to the menu.");
        }
    }
}

// Function to display the user's profile.
void viewProfile(const std::string& name, const std::string& password) {
    system(CLEAR_COMMAND);
    printBorder("VIEW PROFILE");
    std::cout << "Name: " << name << std::endl;
    std::cout << "Password: " << std::string(password.length(), '*') << std::endl; // Mask the password for security.
    pauseForReturn();
}

// Function to change the user's name.
void changeName(std::string& name) {
    system(CLEAR_COMMAND);
    printBorder("CHANGE NAME");

    std::cout << "Your name is currently " << name << ". Are you sure you want to change your name? (y/n): ";
    char confirm;
    std::cin >> confirm;
    inputError("Invalid input. Please enter 'y' or 'n'.");

    if (confirm == 'y' || confirm == 'Y') {
        name = getName();
        nameConfirmation(name);
        std::cout << "Name updated successfully to " << name << "!" << std::endl;
        pauseForReturn();
    } else if (confirm == 'n' || confirm == 'N') {
        std::cout << "Name change cancelled." << std::endl;
        pauseForReturn();
    } else {
        std::cout << "Invalid input. Please enter 'y' or 'n'." << std::endl;
    }
}

// Function to change the user's password
void changePassword(std::string& password) {
    system(CLEAR_COMMAND);
    printBorder("CHANGE PASSWORD");

    std::cout << "Are you sure you want to change your password? (y/n): ";
    char confirm;
    std::cin >> confirm;
    std::cin.ignore(); // ignore newline character

    if (confirm == 'y' || confirm == 'Y') {
        password = getPassword();
        std::cout << "Password updated successfully!" << std::endl;
        pauseForReturn();
    } else {
        std::cout << "Password change cancelled." << std::endl;
        pauseForReturn();
    }
}

// Function to delete the user's profile
void deleteProfile(std::string& name, std::string& password) {
    system(CLEAR_COMMAND);
    printBorder("DELETE PROFILE");
    char confirm;
    std::cout << "Are you sure you want to delete your profile? (y/n): ";
    std::cin >> confirm;
    inputError("Invalid input. Please enter 'y' or 'n'.");

    if (confirm == 'y' || confirm == 'Y') {
        name.clear();
        password.clear();
        saveUserData(name, password); // Clears data in file
        std::cout << "Profile deleted successfully." << std::endl;
    } else {
        std::cout << "Profile deletion canceled." << std::endl;
    }
    pauseForReturn();
}

// Main function to handle profile settings menu.
void profileSettings(std::string& name, std::string& password) {
    int choice;
    do {
        printProfileSettingsMenu(); // Display profile settings menu.
        std::cout << ">>>>> Please select an option: ";
        std::cin >> choice;
        inputError("Invalid input. Please enter a number between 1 and 5.");

        switch (choice) {
            case 1:
                viewProfile(name, password);
                break;
            case 2:
                changeName(name);
                saveUserData(name, password); // Save updated name
                break;
            case 3:
                changePassword(password);
                saveUserData(name, password); // Save updated password
                break;
            case 4:
                deleteProfile(name, password);
                break;
            case 5:
                std::cout << "Returning to the Main Menu..." << std::endl;
                dateTime();
                system(CLEAR_COMMAND); // Clear the screen after profile creation
                printMenu(name); // Display Main Menu after prompting user to exit.
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                pauseForReturn();
                break;
        }
    } while (choice != 5);
}
