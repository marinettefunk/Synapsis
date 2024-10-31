#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>
#include <ctime>
#include "formatting.h"  // Custom formatting like fadeIn, message, etc.
#include "welcome.h"
#include "menu.h"
#include "profile.h"
#include "files.h"

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#define OPEN_COMMAND "start "
#else
#define CLEAR_COMMAND "clear"
#define OPEN_COMMAND "xdg-open "
#endif

// Function to install necessary applications
void installApplication(const std::string& appName) {
#ifdef _WIN32
    std::cout << "Installation is typically manual on Windows." << std::endl;
    std::cout << "Please ensure " << appName << " is installed." << std::endl;
#else
    std::string command;

    if (appName == "xdg-open") {
        command = "sudo apt install xdg-utils";  // Installation command for xdg-utils
    } else if (appName == "gnome-open") {
        command = "sudo apt install gnome-utils";  // Installation command for gnome-utils
    } else if (appName == "kde-open") {
        command = "sudo apt install kde-open";  // Installation command for kde-open
    } else {
        std::cerr << "Unknown application: " << appName << std::endl;
        return;
    }

    std::cout << "Attempting to install " << appName << " using command: " << command << std::endl;
    int result = system(command.c_str());
    if (result == 0) {
        std::cout << appName << " has been successfully installed!" << std::endl;
    } else {
        std::cerr << "Failed to install " << appName << ". Please install it manually." << std::endl;
    }
#endif
}

// Function to open a URL or application
void openAppOrWebsite(const std::string& appOrUrl) {
    std::string command;

#ifdef _WIN32
    command = "start " + appOrUrl;  // For Windows
#else
    command = "xdg-open " + appOrUrl;  // Default for Linux
    int result = system(command.c_str());
    if (result != 0) {
        std::cerr << "xdg-open failed. Attempting gnome-open..." << std::endl;
        command = "gnome-open " + appOrUrl;
        result = system(command.c_str());
        if (result != 0) {
            std::cerr << "gnome-open failed. Attempting kde-open..." << std::endl;
            command = "kde-open " + appOrUrl;
            result = system(command.c_str());
            if (result != 0) {
                std::cerr << "Error opening: " << appOrUrl << std::endl;
                // Ask user if they want to install the missing applications
                std::string installChoice;
                std::cout << "Would you like to install the necessary application? (yes/no): ";
                std::getline(std::cin, installChoice);
                if (installChoice == "yes") {
                    installApplication("xdg-open");
                    installApplication("gnome-open");
                    installApplication("kde-open");
                }
            }
        }
    }
#endif

    std::cout << "Command executed: " << command << std::endl; // Debugging line
}

// Function to detect keywords and respond accordingly
std::string handleUserInput(const std::string& userInput) {
    std::string input = userInput;
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);  // Case-insensitive comparison

    // Detect greetings
    if (input.find("hello") != std::string::npos || 
        input.find("hi") != std::string::npos || 
        input.find("hey") != std::string::npos) {
        return "Hello! How can I assist you today?";
    } 
    // Detect "how are you" inquiry
    else if (input.find("how are you") != std::string::npos ||
             input.find("hi how are you") != std::string::npos ||
             input.find("hello how are you") != std::string::npos ||
             input.find("hey how are you") != std::string::npos ||
             input.find("how do you feel") != std::string::npos) {
        return "I'm just a virtual assistant, but thanks for asking! I'm here and ready to help you, how can I assist?";
    }
    // Detect farewell
    else if (input.find("bye") != std::string::npos || 
             input.find("goodbye") != std::string::npos || 
             input.find("see you") != std::string::npos ||
             input.find("back") != std::string::npos || 
             input.find("exit") != std::string::npos) {
        std::string farewellMessage = "Goodbye! Have a great day!";
        fadeIn(farewellMessage);
        exit(0);  // Exit the program after displaying the message
    }
    // Respond to questions about Synapsis
    else if (input.find("who") != std::string::npos || 
             input.find("tell me about yourself") != std::string::npos ||
             input.find("yourself") != std::string::npos || 
             input.find("your name") != std::string::npos) {
        return "I am SYNAPSIS, your digital assistant here to help you! I am designed to assist with tasks like file management, "
               "opening apps, and more. Just type your queries, and I'll do my best to assist you!";
    }
    // Detect commands to open websites
    else if (input.find("open google") != std::string::npos) {
        openAppOrWebsite("https://www.google.com");
        return "Opening Google in your default browser...";
    } 
    else if (input.find("open youtube") != std::string::npos) {
        openAppOrWebsite("https://www.youtube.com");
        return "Opening YouTube in your default browser.";
    } 
    else if (input.find("open") != std::string::npos) {
        // Check for general websites or applications
        size_t pos = input.find("open ");
        if (pos != std::string::npos) {
            std::string site = input.substr(pos + 5);
            openAppOrWebsite("https://" + site + ".com");
            return "Opening " + site + " in your default browser.";
        }
    }
    // Detect date
    else if (input.find("date") != std::string::npos || 
             input.find("time") != std::string::npos || 
             input.find("day") != std::string::npos) {
        auto now = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
        std::string dateResponse = std::ctime(&currentTime);
        dateResponse.erase(dateResponse.size() - 1); // Remove the newline character
        std::string response = "SYNAPSIS: " + dateResponse;
        return response;
    }
    else if (input.find("name") != std::string::npos || 
             input.find("password") != std::string::npos || 
             input.find("profile") != std::string::npos) {
        return "Opening the Profile Settings Menu...";
    }
    else if (input.find("file") != std::string::npos || 
             input.find("folder") != std::string::npos || 
             input.find("document") != std::string::npos ||
             input.find("spreadsheet") != std::string::npos ||
             input.find("database") != std::string::npos ||   
             input.find("directory") != std::string::npos) {
        return "Opening the File Organiser App...";
    } 
    else if (input.find("main") != std::string::npos || 
             input.find("home") != std::string::npos ||  
             input.find("menu") != std::string::npos) {
        return "Navigating to Main Menu...";
    } 

    // Default response for unrecognized inputs
    return "I'm here to help! Feel free to ask me anything.";
}

// Main ChatBot function
void ChatBot() {
    std::string userInput;
    system(CLEAR_COMMAND);  // Clear console based on OS
    message();  // Initial welcome message

    while (true) {
        std::cout << ">>>>> ";  // User input prompt
        std::getline(std::cin, userInput);

        // Exit if the user wants to leave
        if (userInput == "exit") {
            std::cout << "SYNAPSIS: Goodbye!\n";
            break;
        }

        // Get and display the response
        std::string response = handleUserInput(userInput);
        if (!response.empty()) {  // Avoid printing if the response is an empty string (like after "Goodbye")
            fadeIn("SYNAPSIS: " + response + "\n");  // Display using fadeIn for typing effect
        }
    }
}
