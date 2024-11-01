/*
 * Copyright (c) 2024 Marinette Funk. All rights reserved.
 *
 * This file is part of the SYNAPSIS Project.
 *
 * Description: Virtual Assistant to help with file organisation, with ChatBot NLP functionality.
 *
 * Unauthorized copying of this file, via any medium, is strictly prohibited.
 * Proprietary and confidential.
 *
 * For inquiries, contact: marinettefunk@gmail.com
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <filesystem>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <exception>
#include <chrono>
#include <ctime>
#include <sstream>
#include "formatting.h"
#include "welcome.h"
#include "menu.h"
#include "profile.h"

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

namespace fs = std::filesystem;

// Utility function to format file sizes.
std::string formatFileSize(uintmax_t size) {
    const char* sizes[] = {"B", "KB", "MB", "GB", "TB"};
    int i = 0;
    double dblSize = size;
    while (dblSize > 1024 && i < 4) {
        dblSize /= 1024;
        i++;
    }
    std::ostringstream out;
    out << std::fixed << std::setprecision(2) << dblSize << " " << sizes[i];
    return out.str();
}

// Display Current Directory Path.
void displayCurrentDirectory(const fs::path& currentPath) {
    printBorder("CURRENT DIRECTORY");
    std::cout << "Current Directory: " << currentPath << "\n" << std::endl;
}

// Function to get the file type.
std::string getFileType(const fs::path& path) {
    std::string fileType;
    if (path.extension() == ".txt") fileType = "[TEXT FILE]";
    else if (path.extension() == ".csv") fileType = "[CSV FILE]";
    else if (path.extension() == ".xml") fileType = "[XML FILE]";
    else if (path.extension() == ".json") fileType = "[JSON FILE]";
    else if (path.extension() == ".html") fileType = "[HTML FILE]";
    else if (path.extension() == ".css") fileType = "[CSS FILE]";
    else if (path.extension() == ".js") fileType = "[JAVASCRIPT FILE]";
    else if (path.extension() == ".png") fileType = "[PNG IMAGE]";
    else if (path.extension() == ".jpg" || path.extension() == ".jpeg") fileType = "[JPEG IMAGE]";
    else if (path.extension() == ".gif") fileType = "[GIF IMAGE]";
    else if (path.extension() == ".pdf") fileType = "[PDF FILE]";
    else if (path.extension() == ".doc") fileType = "[WORD DOC]";
    else if (path.extension() == ".docx") fileType = "[WORD DOCX]";
    else if (path.extension() == ".xls") fileType = "[EXCEL XLS]";
    else if (path.extension() == ".xlsx") fileType = "[EXCEL XLSX]";
    else if (path.extension() == ".ppt") fileType = "[POWERPOINT]";
    else if (path.extension() == ".pptx") fileType = "[POWERPOINTX]";
    else if (path.extension() == ".accdb") fileType = "[ACCESS DB]";
    else if (path.extension() == ".mdb") fileType = "[ACCESS MDB]";
    else if (path.extension() == ".zip") fileType = "[ZIP ARCHIVE]";
    else if (path.extension() == ".exe") fileType = "[EXECUTABLE]";
    else if (path.extension() == ".cpp") fileType = "[C++ FILE]";
    else if (path.extension() == ".h") fileType = "[C++ HEADER]";
    else if (path.extension() == ".hpp") fileType = "[C++ HEADER]";
    else if (path.extension() == ".c") fileType = "[C FILE]";
    else if (path.extension() == ".h") fileType = "[C HEADER]";
    else if (path.extension() == ".java") fileType = "[JAVA FILE]";
    else if (path.extension() == ".py") fileType = "[PYTHON FILE]";
    else if (path.extension() == ".php") fileType = "[PHP FILE]";
    else if (path.extension() == ".rb") fileType = "[RUBY FILE]";
    else if (path.extension() == ".swift") fileType = "[SWIFT FILE]";
    else if (path.extension() == ".go") fileType = "[GO FILE]";
    else if (path.extension() == ".kt") fileType = "[KOTLIN FILE]";
    else if (path.extension() == ".scala") fileType = "[SCALA FILE]";
    // Add more conditions for other extensions as needed.
    else fileType = "[OTHER FILE]";

    // Truncate the string to a maximum length of 15 characters.
    if (fileType.length() > 15) {
        fileType = fileType.substr(0, 12) + "...";
    }

    return fileType;
}

// Function to list current directory contents.
void listCurrentDirectory(const fs::path& currentPath) {
    try {
        // Column headers
        std::cout << std::left 
                  << std::setw(15) << "Type" 
                  << std::setw(25) << "Name" 
                  << std::setw(15) << "Size" 
                  << std::endl;
        std::cout << std::string(70, '-') << std::endl;

        // Iterate over entries in the current directory
        for (const auto& entry : fs::directory_iterator(currentPath)) {
            // Determine if it's a file or directory
            std::string type = entry.is_directory() ? "[DIR]" : getFileType(entry.path()).substr(0, 15);
            std::string name = entry.path().filename().string();
            std::string size = entry.is_regular_file() ? formatFileSize(entry.file_size()) : "-";

            // Output the formatted row
            std::cout << std::left 
                      << std::setw(15) << type 
                      << std::setw(25) << name 
                      << std::setw(15) << size 
                      << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error displaying directory contents: " << e.what() << std::endl;
    }
}

// Function for directory navigation.
fs::path navigateToDirectory(const fs::path& currentPath) {
    std::string input;
    std::cout << "Enter the directory name to navigate (or '..' to go up, or '.' to go down): ";
    std::getline(std::cin, input);

    if (input == "..") {
        return currentPath.parent_path(); // Go up to the parent directory.
    } else if (input == ".") {
        // List subdirectories and let the user choose one to go down.
        std::cout << "Subdirectories:" << std::endl;
        for (const auto& entry : fs::directory_iterator(currentPath)) {
            if (entry.is_directory()) {
                std::cout << entry.path().filename().string() << std::endl;
            }
        }
        std::cout << ">>>>> Enter the subdirectory name to go down: ";
        std::getline(std::cin, input);
        fs::path newPath = currentPath / input;
        if (fs::exists(newPath) && fs::is_directory(newPath)) {
            return newPath; // Return the new path if it exists and is a directory.
        } else {
            std::cerr << "Error: Directory not found. Please note that spelling and case must be exact." << std::endl;
            return currentPath; // Stay in the current directory.
        }
    } else {
        fs::path newPath = currentPath / input;
        if (fs::exists(newPath) && fs::is_directory(newPath)) {
            return newPath; // Return the new path if it exists and is a directory.
        } else {
            std::cerr << "Error: Directory not found. Please note that spelling and case must be exact." << std::endl;
            return currentPath; // Stay in the current directory.
        }
    }
}

// Rename File function.
void renameFile(const fs::path& currentPath) {
    system(CLEAR_COMMAND);
    printBorder("RENAME FILE");
    displayCurrentDirectory(currentPath);
    listCurrentDirectory(currentPath);
    std::cout << std::endl;

    char confirm;
    std::string oldName, newName;
    while (true) {
        std::cout << ">>>>> Enter the current file name: ";
        std::getline(std::cin, oldName);

        // Check if the file exists in the directory
        if (!fs::exists(currentPath / oldName)) {
            std::cout << "Error: File '" << oldName << "' not found in the directory. Please note that spelling and case must be exact." << std::endl;
            continue;
        }

        while (true) {
            std::cout << ">>>>> Are you sure you want to change your name? (y/n): ";
            std::cin >> confirm;
            std::cin.ignore();

            if (confirm == 'y' || confirm == 'Y') {
                std::cout << ">>>>> Enter the new file name: ";
                std::getline(std::cin, newName);

                if (newName.empty()) {
                    std::cout << "Error: New file name cannot be empty. Please note that spelling and case must be exact." << std::endl;
                } else {
                    std::cout << "Name updated successfully to " << newName << "!" << std::endl;
                    break;
                }
            } else if (confirm == 'n' || confirm == 'N') {
                std::cout << "Name change cancelled." << std::endl;
                break;
            } else {
                std::cout << "Invalid input. Please enter 'y' or 'n'." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        break;
    }
    pauseForReturn();
    try {
        fs::rename(currentPath / oldName, currentPath / newName);
        std::cout << "File renamed successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error renaming file: " << e.what() << std::endl;
    }
}

// Delete File function.
void deleteFile(const fs::path& currentPath) {
    system(CLEAR_COMMAND);
    printBorder("DELETE FILE");
    displayCurrentDirectory(currentPath);
    listCurrentDirectory(currentPath);
    std::cout << std::endl;

    std::string fileName;
    while (true) {
        std::cout << ">>>>> Enter the file name to delete: ";
        std::getline(std::cin, fileName);

        // Check if the file exists in the directory.
        if (!fs::exists(currentPath / fileName)) {
            std::cout << "Error: File '" << fileName << "' not found in the directory. Please note that spelling and case must be exact." << std::endl;
            continue;
        }

        char confirm;
        while (true) {
            std::cout << ">>>>> Are you sure you want to delete the file? (y/n): ";
            std::cin >> confirm;
            std::cin.ignore();

            if (confirm == 'y' || confirm == 'Y') {
                try {
                    if (fs::remove(currentPath / fileName)) {
                        std::cout << "File deleted successfully!" << std::endl;
                    } else {
                        std::cerr << "File not found." << std::endl;
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Error deleting file: " << e.what() << std::endl;
                }
                break;
            } else if (confirm == 'n' || confirm == 'N') {
                std::cout << "File deletion cancelled." << std::endl;
                break;
            } else {
                std::cout << "Invalid input. Please enter 'y' or 'n'." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        break;
    }
    pauseForReturn();
}

// Function to copy file or directory.
void copyFileOrDir(fs::path& currentPath) {
    system(CLEAR_COMMAND);
    printBorder("COPY FILE");
    displayCurrentDirectory(currentPath);
    listCurrentDirectory(currentPath);
    std::cout << std::endl;

    fs::path sourcePath;
    while (true) {
        std::cout << ">>>>> Enter the source file or directory name: ";
        std::string source;
        std::getline(std::cin, source);

        // Check if the source file or directory exists.
        if (!fs::exists(currentPath / source)) {
            std::cout << "Error: Source '" << source << "' not found in the directory. Please note that spelling and case must be exact." << std::endl;
            continue;
        }

        // Check if the source is a file or directory.
        if (fs::is_directory(currentPath / source)) {
            // Get the absolute path of the source directory.
            sourcePath = fs::absolute(currentPath / source);
        } else if (fs::is_regular_file(currentPath / source)) {
            // Get the absolute path of the source file.
            sourcePath = fs::absolute(currentPath / source);
        } else {
            std::cout << "Error: Source '" << source << "' is not a file or directory." << std::endl;
            continue;
        }

        break;
    }

    std::cout << "Navigate to the destination directory:" << std::endl;
    fs::path destination;

    while (true) {
        std::cout << ">>>>> Enter 'navigate' to change directory or 'stay' to continue in current directory: ";
        std::string userInput;
        std::getline(std::cin, userInput);

        if (userInput == "navigate") {
            currentPath = navigateToDirectory(currentPath);
            displayCurrentDirectory(currentPath);
            listCurrentDirectory(currentPath);
            std::cout << std::endl;
            continue; // Refresh the loop to display the new directory contents
        } else if (userInput == "stay") {
            destination = currentPath;
            break;
        } else {
            std::cout << "Invalid input. Please enter 'navigate' or 'stay'." << std::endl;
        }
    }

    // Check if the destination directory exists.
    if (!fs::exists(destination)) {
        std::cout << "Error: Destination directory '" << destination.string() << "' does not exist." << std::endl;
        return;
    }

    char confirm;
    while (true) {
        std::cout << ">>>>> Are you sure you want to copy the file or directory to '" << destination.string() << "'? (y/n): ";
        std::cin >> confirm;
        std::cin.ignore();

        if (confirm == 'y' || confirm == 'Y') {
            try {
                // Check if the source and destination are the same
                if (sourcePath == destination) {
                    std::cout << "Error: Source and destination are the same." << std::endl;
                    continue;
                }

                fs::copy(sourcePath, destination, fs::copy_options::overwrite_existing | fs::copy_options::recursive);
                std::cout << "Copied successfully!" << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error copying: " << e.what() << std::endl;
            }
            break;
        } else if (confirm == 'n' || confirm == 'N') {
            std::cout << "Copy operation cancelled." << std::endl;
            break;
        } else {
            std::cout << "Invalid input. Please enter 'y' or 'n'." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    pauseForReturn();
}

// Function to move file or directory.
void moveFileOrDir(fs::path& currentPath) {
    system(CLEAR_COMMAND);
    printBorder("MOVE FILE");
    displayCurrentDirectory(currentPath);
    listCurrentDirectory(currentPath);
    std::cout << std::endl;

    fs::path sourcePath;
    while (true) {
        std::cout << ">>>>> Enter the source file or directory name: ";
        std::string source;
        std::getline(std::cin, source);

        // Check if the source file or directory exists.
        if (!fs::exists(currentPath / source)) {
            std::cout << "Error: Source '" << source << "' not found in the directory. Please note that spelling and case must be exact." << std::endl;
            continue;
        }

        // Check if the source is a file or directory.
        if (fs::is_directory(currentPath / source)) {
            // Get the absolute path of the source directory.
            sourcePath = fs::absolute(currentPath / source);
        } else if (fs::is_regular_file(currentPath / source)) {
            // Get the absolute path of the source file.
            sourcePath = fs::absolute(currentPath / source);
        } else {
            std::cout << "Error: Source '" << source << "' is not a file or directory." << std::endl;
            continue;
        }

        break;
    }

    std::cout << "Navigate to the destination directory:" << std::endl;
    fs::path destination;

    while (true) {
        std::cout << ">>>>> Enter 'navigate' to change directory or 'stay' to continue in current directory: ";
        std::string userInput;
        std::getline(std::cin, userInput);

        if (userInput == "navigate") {
            currentPath = navigateToDirectory(currentPath);
            displayCurrentDirectory(currentPath);
            listCurrentDirectory(currentPath);
            std::cout << std::endl;
            continue; // Refresh the loop to display the new directory contents.
        } else if (userInput == "stay") {
            destination = currentPath;
            break;
        } else {
            std::cout << "Invalid input. Please enter 'navigate' or 'stay'." << std::endl;
        }
    }

    // Check if the destination directory exists.
    if (!fs::exists(destination)) {
        std::cout << "Error: Destination directory '" << destination.string() << "' does not exist." << std::endl;
        return;
    }

    char confirm;
    while (true) {
        std::cout << ">>>>> Are you sure you want to move the file or directory to '" << destination.string() << "'? (y/n): ";
        std::cin >> confirm;
        std::cin.ignore();

        if (confirm == 'y' || confirm == 'Y') {
            try {
                // Check if the source and destination are the same.
                if (sourcePath == destination) {
                    std::cout << "Error: Source and destination are the same." << std::endl;
                    continue;
                }

                fs::rename(sourcePath, destination / sourcePath.filename());
                std::cout << "File or directory moved successfully." << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error moving file or directory: " << e.what() << std::endl;
            }
            break;
        } else if (confirm == 'n' || confirm == 'N') {
            std::cout << "File or directory move operation cancelled." << std::endl;
            break;
        } else {
            std::cout << "Invalid input. Please enter 'y' or 'n'." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    pauseForReturn();
}


// Display menu for File Organiser App.
void printFileOrganiserMenu() {
    printBorder("WHAT DO YOU WANT TO DO?");
    std::cout << "1. Rename File\n"
              << "2. Delete File\n"
              << "3. Copy File\n"
              << "4. Move File\n"
              << "5. Back to Main Menu" << std::endl;
}

// Main File Organiser Application Function.
void fileOrganiserApp() {
    fs::path currentPath = fs::current_path(); // Set current directory.
    
    while (true) {
        system(CLEAR_COMMAND);
        dateTime();
        printLogo();
        displayCurrentDirectory(currentPath);
        listCurrentDirectory(currentPath);

        std::cout << std::endl;
        printFileOrganiserMenu();
        std::cout << std::endl;

        // Add option to navigate directories.
        std::cout << "First, navigate or stay in desired directory:" << std::endl;
        std::cout << ">>>>> Enter 'navigate' to change directory, or choose an option: ";
        
        std::string userInput;
        std::getline(std::cin, userInput);

        if (userInput == "navigate") {
            currentPath = navigateToDirectory(currentPath);
            continue; // Refresh the loop to display the new directory contents.
        }

        int choice;
        try {
            choice = std::stoi(userInput); // Convert string input to int.
        } catch (...) {
            std::cout << "Invalid choice. Please enter a number or 'navigate'." << std::endl;
            system("pause");
            continue; // Go back to the start of the loop.
        }

        // Validate the choice
        if (choice < 1 || choice > 6) {
            std::cout << ">>>>> Invalid choice. Please choose again: ";
            system("pause");
            continue;
        }

        switch (choice) {
            case 1:
                renameFile(currentPath);
                break;
            case 2:
                deleteFile(currentPath);
                break;
            case 3:
                copyFileOrDir(currentPath);
                break;
            case 4:
                moveFileOrDir(currentPath);
                break;
            case 5:
                std::string name, password;
                loadUserData(name, password);
                printMenu(name);
                break;
        }
        system("pause"); // Wait for user input before continuing.
    }
}