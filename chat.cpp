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
#elif __APPLE__
#define CLEAR_COMMAND "clear"
#define OPEN_COMMAND "open "  // For macOS
#else
#define CLEAR_COMMAND "clear"
#define OPEN_COMMAND "powershell.exe /c start "  // For WSL on Windows
#endif

// Function to URL encode the search query
std::string urlEncode(const std::string& query) {
    std::string encoded;
    for (char c : query) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            encoded += c;
        } else if (c == ' ') {
            encoded += "+";
        } else {
            char hex[4];
            snprintf(hex, sizeof(hex), "%%%02X", static_cast<unsigned char>(c));
            encoded += hex;
        }
    }
    return encoded;
}

// Function to perform a Google search
void googleSearch(const std::string& query) {
    std::string encodedQuery = urlEncode(query);
    std::string url = "https://www.google.com/search?q=" + encodedQuery;

    // Determine the command based on the operating system
    std::string command;

    #ifdef _WIN32
        command = "start " + url;
    #elif __APPLE__
        command = "open " + url;
    #else // Linux and other UNIX-like OS
        command = OPEN_COMMAND + url;  // Use PowerShell command for WSL
    #endif

    system(command.c_str());
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
        std::cout << "SYNAPSIS: " << farewellMessage << std::endl; // Directly print without fade effect
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
    // Detect date
    else if (input.find("date") != std::string::npos || 
             input.find("time") != std::string::npos || 
             input.find("day") != std::string::npos) {
        auto now = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
        std::string dateResponse = std::ctime(&currentTime);
        dateResponse.erase(dateResponse.size() - 1); // Remove the newline character
        return "SYNAPSIS: " + dateResponse;
    }
    else if (input.find("name") != std::string::npos || 
             input.find("password") != std::string::npos || 
             input.find("profile") != std::string::npos) {
            std::string name, password;
            loadUserData(name, password);
            profileSettings(name, password);
        return "Opening the Profile Settings Menu...";
    }
    else if (input.find("file") != std::string::npos || 
             input.find("folder") != std::string::npos || 
             input.find("document") != std::string::npos ||
             input.find("spreadsheet") != std::string::npos ||
             input.find("database") != std::string::npos ||   
             input.find("directory") != std::string::npos) {
        fileOrganiserApp();        
        return "Opening the File Organizer App...";
    } 
    else if (input.find("main") != std::string::npos || 
             input.find("home") != std::string::npos ||  
             input.find("menu") != std::string::npos) {
        return "Navigating to Main Menu...";
    } 
    // Detect Google search request
    else if (input.find("google") != std::string::npos ||
             input.find("search") != std::string::npos) {
        std::cout << "What would you like to search for? ";
        std::string searchQuery;
        std::getline(std::cin, searchQuery);
        googleSearch(searchQuery);
        return "Searching Google for \"" + searchQuery + "\"...";
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
            std::cout << "SYNAPSIS: " << response << std::endl; // Print without fadeIn for simplicity
        }
    }
}
