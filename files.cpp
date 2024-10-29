#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <filesystem>
#include <vector>
#include <algorithm>
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

namespace fs = std::filesystem;

void renameFile() {
    std::string oldName, newName;
    std::cout << "Enter the current file name: ";
    std::getline(std::cin, oldName);
    std::cout << "Enter the new file name: ";
    std::getline(std::cin, newName);

    try {
        fs::rename(oldName, newName);
        std::cout << "File renamed successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error renaming file: " << e.what() << std::endl;
    }
}

void deleteFile() {
    std::string fileName;
    std::cout << "Enter the file name to delete: ";
    std::getline(std::cin, fileName);

    try {
        if (fs::remove(fileName)) {
            std::cout << "File deleted successfully." << std::endl;
        } else {
            std::cerr << "File not found." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error deleting file: " << e.what() << std::endl;
    }
}

void copyFile() {
    std::string source, destination;
    std::cout << "Enter the source file name: ";
    std::getline(std::cin, source);
    std::cout << "Enter the destination file name: ";
    std::getline(std::cin, destination);

    try {
        fs::copy(source, destination, fs::copy_options::overwrite_existing);
        std::cout << "File copied successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error copying file: " << e.what() << std::endl;
    }
}

void moveFile() {
    std::string source, destination;
    std::cout << "Enter the source file name: ";
    std::getline(std::cin, source);
    std::cout << "Enter the destination path: ";
    std::getline(std::cin, destination);

    try {
        fs::rename(source, destination);
        std::cout << "File moved successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error moving file: " << e.what() << std::endl;
    }
}

void reorderFiles() {
    std::string directory;
    std::cout << "Enter the directory path: ";
    std::getline(std::cin, directory);

    try {
        std::vector<fs::path> files;
        for (const auto& entry : fs::directory_iterator(directory)) {
            if (fs::is_regular_file(entry)) {
                files.push_back(entry.path());
            }
        }
        std::sort(files.begin(), files.end());

        for (const auto& file : files) {
            std::cout << file.filename() << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error reading directory: " << e.what() << std::endl;
    }
}

void handleFileOrganiserChoice(int choice) {
    switch (choice) {
        case 1: renameFile(); break;
        case 2: deleteFile(); break;
        case 3: copyFile(); break;
        case 4: moveFile(); break;
        case 5: reorderFiles(); break;
        case 6: std::cout << "Returning to Main Menu..." << std::endl; break;
        default: std::cout << "Invalid choice." << std::endl; break;
    }
}

void fileOrganiserApp() {
    int choice;
    while (true) {
        printFileOrganiser();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        handleFileOrganiserChoice(choice);
        if (choice == 6) break;
    }

}
