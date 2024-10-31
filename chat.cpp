#include <iostream>
#include <string>
#include <algorithm>
#include "formatting.h"
#include "welcome.h"
#include "menu.h"
#include "profile.h"
#include "files.h"

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

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
    // Detect farewell
    else if (input.find("bye") != std::string::npos || 
             input.find("goodbye") != std::string::npos || 
             input.find("see you") != std::string::npos ||
             input.find("exit") != std::string::npos) {
        fadeIn("Goodbye! Have a great day!");
        return "";  // Indicate the farewell message is displayed
    }
    // Respond to questions about Synapsis
    else if (input.find("who") != std::string::npos || 
             input.find("what") != std::string::npos || 
             input.find("tell me about yourself") != std::string::npos ||
             input.find("yourself") != std::string::npos||
             input.find("your name") != std::string::npos) {
        return "I am SYNAPSIS, your digital assistant here to help you! I am designed to help with file management and other tasks. "
               "Just type your queries, and I'll do my best to assist you!";
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