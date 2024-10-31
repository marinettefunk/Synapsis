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
#define ESPEAK_COMMAND "espeak.exe "  // Ensure espeak.exe is in the PATH
#else
#define CLEAR_COMMAND "clear"
#define OPEN_COMMAND "xdg-open "
#define ESPEAK_COMMAND "espeak "
#endif

// Function to call espeak for text-to-speech
void speak(const std::string& text) {
    std::string command = ESPEAK_COMMAND + std::string("\"") + text + "\"";
    system(command.c_str());
}

// Function to open a URL or application
void openAppOrWebsite(const std::string& appOrUrl) {
    std::string command = OPEN_COMMAND + appOrUrl;
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
        fadeIn("Goodbye! Have a great day!");
        speak("Goodbye! Have a great day!"); // Speak the farewell
        exit(0);
        return "";  // Indicate the farewell message is displayed
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
            if (site == "google") {
                openAppOrWebsite("https://www.google.com");
                return "Opening Google in your default browser.";
            } else if (site == "youtube") {
                openAppOrWebsite("https://www.youtube.com");
                return "Opening YouTube in your default browser.";
            } else {
                openAppOrWebsite("https://" + site + ".com");
                return "Opening " + site + " in your default browser.";
            }
        }
    }
    // Detect date
    else if (input.find("date") != std::string::npos || 
             input.find("time") != std::string::npos || 
             input.find("day") != std::string::npos) {
        auto now = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
        fadeIn(std::string(std::ctime(&currentTime)));
        speak(std::string(std::ctime(&currentTime))); // Speak the date/time
        return "";  // Indicate the farewell message is displayed
    }

    else if (input.find("name") != std::string::npos || 
    input.find("password") != std::string::npos || 
    input.find("profile") != std::string::npos) {
        return "Opening the Profile Settings Menu";
        std::string name, password;
        loadUserData(name, password);
        profileSettings(name, password); // Pass both name and password
    }

    else if (input.find("file") != std::string::npos || 
        input.find("folder") != std::string::npos || 
        input.find("document") != std::string::npos ||
        input.find("spreadheet") != std::string::npos ||
        input.find("database") != std::string::npos ||   
        input.find("directory") != std::string::npos) {
        return "Opening the File Organiser App";
        fileOrganiserApp();
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
            speak("Goodbye!"); // Speak goodbye
            break;
        }

        // Get and display the response
        std::string response = handleUserInput(userInput);
        if (!response.empty()) {  // Avoid printing if the response is an empty string (like after "Goodbye")
            fadeIn("SYNAPSIS: " + response + "\n");  // Display using fadeIn for typing effect
            speak(response);  // Speak the response
        }
    }
}
