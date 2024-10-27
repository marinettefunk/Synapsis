#include <iostream>
#include <string>
#include <fstream>
#include <limits> // Required for numeric_limits
#include "formatting.h"
#include "welcome.h"

#ifdef _WIN32
#define CLEAR_COMMAND "cls" // Windows
#else
#define CLEAR_COMMAND "clear" // Unix/Linux, macOS
#endif

// Function to load user data from file
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

// Function to save user data to file
void saveUserData(const std::string& name, const std::string& password) {
    std::ofstream file("user_data.txt");
    if (file.is_open()) {
        file << name << std::endl;
        file << password << std::endl;
        file.close();
    }
}

// Function to get user name
std::string getName() {
    std::string name;
    std::cout << ">>>>> Please enter your name: ";
    std::getline(std::cin, name);
    return name;
}

// Function to confirm user name
void nameConfirmation(std::string& name) {
    char confirm = '\0';
    do {
        std::cout << ">>>>> Your name is " << name << ". Is this correct? (y/n): ";
        std::cin >> confirm;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the newline character

        if (confirm == 'y' || confirm == 'Y') {
            break;
        } else if (confirm == 'n' || confirm == 'N') {
            std::cout << ">>>>> Please enter your name: ";
            std::getline(std::cin, name);
        } else {
            std::cout << "Invalid input. Please enter 'y' or 'n'." << std::endl;
        }
    } while (true);
}

// Function to get password
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

// Function to create a profile
void createProfile(std::string& name, std::string& password) {
    std::string message = "FIRST, LET'S CREATE YOUR PROFILE";
    printWithModernBorder(message);
    name = getName();
    nameConfirmation(name);
    password = getPassword();
    saveUserData(name, password);

    system(CLEAR_COMMAND); // Clear the screen after profile creation
    std::cout << "Profile created successfully!\nHello, " << name << "! What can I help you with today?" << std::endl;
}

// Function to run the program
void runProgram() {
    std::string name;
    std::string password;

    loadUserData(name, password);

    if (name.empty() || password.empty()) {
        createProfile(name, password);
    } else {
        std::cout << "Welcome back, " + name + "!"<< std::endl;
        std::string inputPassword;
        std::cout << ">>>>> Please enter your password: ";
        std::getline(std::cin, inputPassword);

        if (inputPassword == password) {
            system(CLEAR_COMMAND); // Clear the screen after successful login
            printLogo();
            std::cout << std::endl;
            std::cout << "Hello, " + name + "! What can I help you with today?" << std::endl;
            std::cout << std::endl;
        } else {
            std::cout << "Incorrect password." << std::endl;
        }
    }
}

void printProfile (){
    system(CLEAR_COMMAND); // Clear the screen after successful login
    printLogo();
    std::cout << std::endl;
    printWithModernBorder("PROFILE SETTINGS");
    std::cout << "1. View Profile" << std::endl;
    std::cout << "2. Change Name" << std::endl;
    std::cout << "3. Change Password" << std::endl;
    std::cout << "4. Delete Profile" << std::endl;
    std::cout << "5. Back to Main Menu" << std::endl;
    std::cout << std::endl;

    int choice;
    std::cout << ">>>>> Please select an option: ";
    std::cin >> choice;
    
}
