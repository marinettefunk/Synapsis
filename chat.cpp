#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>
#include <ctime>
#include "formatting.h"
#include "menu.h"
#include "welcome.h"
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

// Function to URL encode the search query.
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

// Function to perform a Google search.
void googleSearch(const std::string& query) {
    std::string encodedQuery = urlEncode(query);
    std::string url = "https://www.google.com/search?q=" + encodedQuery;
    system((OPEN_COMMAND + url).c_str());
}

// Function to perform a YouTube search.
void youtubeSearch(const std::string& query) {
    std::string encodedQuery = urlEncode(query);
    std::string url = "https://www.youtube.com/results?search_query=" + encodedQuery;
    system((OPEN_COMMAND + url).c_str());
}

// Function to perform a Spotify search.
void spotifySearch(const std::string& query) {
    std::string encodedQuery = urlEncode(query);
    std::string url = "https://open.spotify.com/search/" + encodedQuery;
    system((OPEN_COMMAND + url).c_str());
}

// Function to perform a Wikipedia search.
void wikipediaSearch(const std::string& query) {
    std::string encodedQuery = urlEncode(query);
    std::string url = "https://en.wikipedia.org/wiki/Special:Search?search=" + encodedQuery;
    system((OPEN_COMMAND + url).c_str());
}

// Function to open WhatsApp.
void openWhatsApp() {
    std::string url = "https://web.whatsapp.com";
    system((OPEN_COMMAND + url).c_str());
}

// Function to open Instagram
void openInstagram() {
    std::string url = "https://www.instagram.com";
    system((OPEN_COMMAND + url).c_str());
}

// Function to open Twitter.
void openTwitter() {
    std::string url = "https://twitter.com";
    system((OPEN_COMMAND + url).c_str());
}

// Function to open Facebook.
void openFacebook() {
    std::string url = "https://www.facebook.com";
    system((OPEN_COMMAND + url).c_str());
}

// Function to open LinkedIn.
void openLinkedIn() {
    std::string url = "https://www.linkedin.com";
    system((OPEN_COMMAND + url).c_str());
}

// Function to detect keywords and respond accordingly.
std::string handleUserInput(const std::string& userInput) {
    std::string input = userInput;
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);  // Case-insensitive comparison

    // Detect greetings.
    if (input.find("hello") != std::string::npos || 
        input.find("hi") != std::string::npos || 
        input.find("hey") != std::string::npos) {
        return "SYNAPSIS: Hello! How can I assist you today?\n";
    } 
    // Detect "how are you" inquiry.
    else if (input.find("how are you") != std::string::npos ||
             input.find("hi how are you") != std::string::npos ||
             input.find("hello how are you") != std::string::npos ||
             input.find("hey how are you") != std::string::npos ||
             input.find("how do you feel") != std::string::npos) {
        return "SYNAPSIS: I'm just a virtual assistant, but thanks for asking! I'm here and ready to help you, how can I assist?\n";
    }
    // Detect farewell.
    else if (input.find("bye") != std::string::npos || 
             input.find("goodbye") != std::string::npos || 
             input.find("see you") != std::string::npos ||
             input.find("back") != std::string::npos || 
             input.find("exit") != std::string::npos) {
        std::string farewellMessage = "Goodbye! Have a great day!";
        std::cout << "SYNAPSIS: " << farewellMessage << std::endl; // Directly print without fade effect
        exit(0);  // Exit the program after displaying the message
    }
    // Respond to questions about SYNAPSIS.
    else if (input.find("who") != std::string::npos || 
             input.find("tell me about yourself") != std::string::npos ||
             input.find("yourself") != std::string::npos || 
             input.find("your name") != std::string::npos) {
        return "SYNAPSIS: I am SYNAPSIS, your digital assistant here to help you! I am designed to assist with tasks like file management, "
               "opening apps, and more. Just type your queries, and I'll do my best to assist you!\n";
    }
    // Detect date.
    else if (input.find("date") != std::string::npos || 
             input.find("time") != std::string::npos || 
             input.find("day") != std::string::npos) {
        auto now = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
        std::string dateResponse = std::ctime(&currentTime);
        dateResponse.erase(dateResponse.size() - 1); // Remove the newline character
        return "SYNAPSIS: " + dateResponse + "\n";
    }
    // Detect Profile Settings changes.
    else if (input.find("name") != std::string::npos || 
             input.find("password") != std::string::npos || 
             input.find("profile") != std::string::npos) {
        std::string name, password;
        loadUserData(name, password);
        profileSettings(name, password);
        return "SYNAPSIS: Opening the Profile Settings Menu...\n";
    }
    // Detect using File Organiser App.
    else if (input.find("file") != std::string::npos || 
             input.find("folder") != std::string::npos || 
             input.find("document") != std::string::npos ||
             input.find("spreadsheet") != std::string::npos ||
             input.find("database") != std::string::npos ||   
             input.find("directory") != std::string::npos) {
        fileOrganiserApp();        
        return "SYNAPSIS: Opening the File Organizer App...\n";
    } 
    // Detect going to Main Menu.
    else if (input.find("main") != std::string::npos || 
             input.find("home") != std::string::npos ||  
             input.find("menu") != std::string::npos) {
        return "SYNAPSIS: Navigating to Main Menu...\n";
    } 
    // Detect Google search request.
    else if (input.find("google") != std::string::npos ||
             input.find("search") != std::string::npos) {
        std::cout << "SYNAPSIS: What would you like to search for? ";
        std::string searchQuery;
        std::getline(std::cin, searchQuery);
        googleSearch(searchQuery);
        return "SYNAPSIS: Searching Google for \"" + searchQuery + "\"...\n";
    }
    // Detect YouTube search request.
    else if (input.find("youtube") != std::string::npos) {
        std::cout << "SYNAPSIS: What would you like to search for on YouTube? ";
        std::string searchQuery;
        std::getline(std::cin, searchQuery);
        youtubeSearch(searchQuery);
        return "SYNAPSIS: Searching YouTube for \"" + searchQuery + "\"...\n";
    }
    // Detect Spotify search request.
    else if (input.find("spotify") != std::string::npos) {
        std::cout << "SYNAPSIS: What would you like to search for on Spotify? ";
        std::string searchQuery;
        std::getline(std::cin, searchQuery);
        spotifySearch(searchQuery);
        return "SYNAPSIS: Searching Spotify for \"" + searchQuery + "\"...\n";
    }
    // Detect Wikipedia search request.
    else if (input.find("wikipedia") != std::string::npos) {
        std::cout << "SYNAPSIS: What would you like to search for on Wikipedia? ";
        std::string searchQuery;
        std::getline(std::cin, searchQuery);
        wikipediaSearch(searchQuery);
        return "SYNAPSIS: Searching Wikipedia for \"" + searchQuery + "\"...\n";
    }
    // Detect social media requests.
    else if (input.find("whatsapp") != std::string::npos) {
        openWhatsApp();
        return "SYNAPSIS: Opening WhatsApp...\n";
    }
    else if (input.find("instagram") != std::string::npos) {
        openInstagram();
        return "SYNAPSIS: Opening Instagram...\n";
    }
    else if (input.find("twitter") != std::string::npos) {
        openTwitter();
        return "SYNAPSIS: Opening Twitter...\n";
    }
    else if (input.find("facebook") != std::string::npos) {
        openFacebook();
        return "SYNAPSIS: Opening Facebook...\n";
    }
    else if (input.find("linkedin") != std::string::npos) {
        openLinkedIn();
        return "SYNAPSIS: Opening LinkedIn...\n";
    }

    // Default response for unrecognized inputs.
    return "I'm here to help! Feel free to ask me anything.";
}

// Main ChatBot function.
void ChatBot() {
    std::string userInput;
    system(CLEAR_COMMAND);  // Clear console based on OS.
    message();  // Initial welcome message.

    while (true) {
        std::cout << ">>>>> ";  // User input prompt.
        std::getline(std::cin, userInput);

        // Get and display the response.
        std::string response = handleUserInput(userInput);
        if (!response.empty()) {  // Avoid printing if the response is empty.
            std::cout << response << std::endl;
        }
    }
}