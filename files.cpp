#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <string>
#include "formatting.h"
#include "welcome.h"
#include "menu.h"

#ifdef _WIN32
#define CLEAR_COMMAND "cls" // Windows
#else
#define CLEAR_COMMAND "clear" // Unix/Linux, macOS
#endif

void printFileOrganiser() {
    system(CLEAR_COMMAND); // Clear the screen
    dateTime();
    printLogo();
    std::cout << std::endl;
    printBorder("FILE ORGANISER");
    std::cout << "1. Rename File" << std::endl;
    std::cout << "2. Delete File" << std::endl;
    std::cout << "3. Copy File" << std::endl;
    std::cout << "4. Move File" << std::endl;
    std::cout << "5. Re-order Files" << std::endl;
    std::cout << "6. Back to Main Menu" << std::endl;
    std::cout << std::endl;
}

void path() {
    // Prompt the user to enter the path
    std::string path;
    std::cout << "Enter the path to the directory: ";
    std::getline(std::cin, path);

    // Wrap path in quotes to handle spaces
    path = "\"" + path + "\"";

    // Determine the command based on the operating system
    std::string command;
    #ifdef _WIN32
        command = "dir /a-d /b ";
    #else
        command = "ls -p ";
    #endif

    // Append the user-provided path to the command
    command.append(path);

    // Execute the command
    std::system(command.c_str());

}

