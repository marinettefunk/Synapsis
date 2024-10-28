#include <iostream>
#include <string>
#include <algorithm>
#include "welcome.h"
#include "formatting.h"

#ifdef _WIN32
#define CLEAR_COMMAND "cls" // Windows
#else
#define CLEAR_COMMAND "clear" // Unix/Linux, macOS
#endif

std::string toLowerCase(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::string getResponse(const std::string& input) {
    std::string lowerInput = toLowerCase(input);

    if (lowerInput == "hello" || lowerInput == "hi") {
        return "Hello! How can I assist you today?";
    } else if (lowerInput == "how are you?") {
        return "I'm just a weatherbot, but thank you for asking! How are you?";
    } else if (lowerInput == "what's your name?") {
        return "Imm a simple weatherbot created in C++. Nice to meet you!";
    } else if (lowerInput == "bye" || lowerInput == "goodbye") {
        return "Goodbye! Have a great day!";
    } else {
        return "I'm not sure how to respond to that. Could you ask something else?";
    }
}

void weatherBot() {
    std::string userInput;
    
    system(CLEAR_COMMAND); // Clear the screen after profile creation
    dateTime();
    printLogo();
    std::cout << std::endl;
    printBorder("WELCOME TO SYNAPSIS weatherBOT");

    std::cout << "Hello! What can I help you with today?" << std::endl;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, userInput);

        if (toLowerCase(userInput) == "bye") {
            std::cout << "Goodbye! Have a great day!\n";
            break;
        }

        if (!userInput.empty()) {
            std::string response = getResponse(userInput);
            std::cout << response << "\n";
        }
    }
}
