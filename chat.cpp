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
        input.find("hey") != std::string::npos || 
        input.find("greetings") != std::string::npos ||
        input.find("greetings") != std::string::npos ||
        input.find("greetings") != std::string::npos ||
        input.find("good day") != std::string::npos ||
        input.find("good morning") != std::string::npos ||
        input.find("good evening") != std::string::npos ||
        input.find("sup") != std::string::npos) {
        return "SYNAPSIS: Hello! How can I assist you?\n";
    } 
    // Detect "how are you" inquiry.
    else if (input.find("how are you") != std::string::npos ||
             input.find("how is it going") != std::string::npos ||
             input.find("what's up") != std::string::npos) {
        return "SYNAPSIS: I'm doing great—virtually unstoppable, actually! How can I help you?\n";
    }
    // Detect farewell.
    else if (input.find("bye") != std::string::npos || 
             input.find("goodbye") != std::string::npos || 
             input.find("see you") != std::string::npos ||
             input.find("later") != std::string::npos || 
             input.find("good night") != std::string::npos ||
             input.find("exit") != std::string::npos) {
        std::string farewellMessage = "SYNAPSIS: Until next time!";
        std::cout << farewellMessage << std::endl; // Directly print without fade effect
        exit(0);  // Exit the program after displaying the message
    }
    // Respond to questions about SYNAPSIS.
    else if (input.find("who") != std::string::npos || 
             input.find("tell me about yourself") != std::string::npos ||
             input.find("about you") != std::string::npos || 
             input.find("your name") != std::string::npos ||
             input.find("your origin") != std::string::npos) {
        return "SYNAPSIS: I am SYNAPSIS, your friendly digital assistant. I’m programmed to help with tasks - like file organisation, answer questions, and many other things!\n";
    }
    // Detect date.
    else if (input.find("date") != std::string::npos || 
             input.find("time") != std::string::npos || 
             input.find("day") != std::string::npos) {
        auto now = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
        std::string dateResponse = std::ctime(&currentTime);
        dateResponse.erase(dateResponse.size() - 1); // Remove the newline character.
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
    else if (input.find("facebook") != std::string::npos) {
        openFacebook();
        return "SYNAPSIS: Opening Facebook...\n";
    }
    else if (input.find("linkedin") != std::string::npos) {
        openLinkedIn();
        return "SYNAPSIS: Opening LinkedIn...\n";
    }
    // Detect fun fact request.
else if (input.find("fact") != std::string::npos) {
    srand(time(0));  // Seed for randomness.
    int factIndex = rand() % 20;

    switch (factIndex) {
        case 0:
            return "SYNAPSIS: Did you know? Honey never spoils. Archaeologists have found pots of honey in ancient Egyptian tombs that are over 3,000 years old and still perfectly edible!\n";
        case 1:
            return "SYNAPSIS: Fun fact: Octopuses have three hearts and blue blood. Two hearts pump blood to the gills, while the third pumps it to the rest of the body.\n";
        case 2:
            return "SYNAPSIS: Bananas are berries, but strawberries aren't! Botanically speaking, a berry has seeds on the inside.\n";
        case 3:
            return "SYNAPSIS: Did you know? The Eiffel Tower can be 15 cm taller during the summer due to thermal expansion.\n";
        case 4:
            return "SYNAPSIS: Sea otters hold hands when they sleep so they don’t drift apart.\n";
        case 5:
            return "SYNAPSIS: A group of flamingos is called a 'flamboyance.'\n";
        case 6:
            return "SYNAPSIS: The shortest war in history was between Britain and Zanzibar on August 27, 1896. Zanzibar surrendered after 38 minutes.\n";
        case 7:
            return "SYNAPSIS: Did you know? Some cats are allergic to humans!\n";
        case 8:
            return "SYNAPSIS: There are more stars in the universe than grains of sand on all the Earth's beaches.\n";
        case 9:
            return "SYNAPSIS: The heart of a shrimp is located in its head.\n";
        case 10:
            return "SYNAPSIS: A snail can sleep for three years at a time.\n";
        case 11:
            return "SYNAPSIS: The longest time between two twins being born is 87 days.\n";
        case 12:
            return "SYNAPSIS: Did you know? The moon has moonquakes, similar to earthquakes on Earth.\n";
        case 13:
            return "SYNAPSIS: Cows have best friends and can become stressed when separated from them.\n";
        case 14:
            return "SYNAPSIS: Did you know? Slugs have four noses.\n";
        case 15:
            return "SYNAPSIS: The inventor of the Frisbee was turned into a Frisbee after he died.\n";
        case 16:
            return "SYNAPSIS: You can hear a blue whale's heartbeat from more than 2 miles away.\n";
        case 17:
            return "SYNAPSIS: The electric chair was invented by a dentist.\n";
        case 18:
            return "SYNAPSIS: Butterflies taste with their feet.\n";
        case 19:
            return "SYNAPSIS: Polar bears have black skin under their white fur.\n";
    }
}

// Detect joke request.
else if (input.find("joke") != std::string::npos) {
    srand(time(0));  // Seed for randomness.
    int jokeIndex = rand() % 20; 

    switch (jokeIndex) {
        case 0:
            return "SYNAPSIS: Why don't scientists trust atoms? Because they make up everything!\n";
        case 1:
            return "SYNAPSIS: Why did the scarecrow win an award? Because he was outstanding in his field!\n";
        case 2:
            return "SYNAPSIS: Why did the math book look sad? Because it had too many problems.\n";
        case 3:
            return "SYNAPSIS: Why can't you give Elsa a balloon? Because she will let it go.\n";
        case 4:
            return "SYNAPSIS: What did one wall say to the other? I'll meet you at the corner.\n";
        case 5:
            return "SYNAPSIS: Why was the broom late? It swept in!\n";
        case 6:
            return "SYNAPSIS: What do you call fake spaghetti? An *impasta*.\n";
        case 7:
            return "SYNAPSIS: What did the janitor say when he jumped out of the closet? Supplies!\n";
        case 8:
            return "SYNAPSIS: Why couldn't the bicycle stand up by itself? It was two tired.\n";
        case 9:
            return "SYNAPSIS: What do you call cheese that isn't yours? Nacho cheese.\n";
        case 10:
            return "SYNAPSIS: Why did the computer go to therapy? It had a hard drive.\n";
        case 11:
            return "SYNAPSIS: Why did the skeleton go to the party alone? He had no body to go with him.\n";
        case 12:
            return "SYNAPSIS: What did the grape do when he got stepped on? Nothing, he just let out a little *whine*.\n";
        case 13:
            return "SYNAPSIS: Why do cows wear bells? Because their horns don't work.\n";
        case 14:
            return "SYNAPSIS: What did the left eye say to the right eye? Between us, something smells.\n";
        case 15:
            return "SYNAPSIS: Why don't skeletons fight each other? They don't have the guts.\n";
        case 16:
            return "SYNAPSIS: What do you get when you cross a snowman with a vampire? Frostbite.\n";
        case 17:
            return "SYNAPSIS: How does a penguin build its house? Igloos it together.\n";
        case 18:
            return "SYNAPSIS: What do you call a factory that makes okay products? A satisfactory.\n";
        case 19:
            return "SYNAPSIS: Why did the tomato blush? Because it saw the salad dressing.\n";
    }
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