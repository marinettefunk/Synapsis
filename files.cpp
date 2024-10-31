#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <filesystem>
#include <vector>
#include <iomanip> // For column formatting
#include <limits> // For ignoring input limits
#include <algorithm>
#include <exception>
#include <chrono> // For time handling
#include <ctime> // For converting time to readable format
#include <sstream> // For string stream
#include "formatting.h"
#include "welcome.h"
#include "menu.h"

#ifdef _WIN32
#define CLEAR_COMMAND "cls" // Windows
#else
#define CLEAR_COMMAND "clear" // Unix/Linux, macOS
#endif

namespace fs = std::filesystem;

// Utility function to format file sizes
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

// Display Current Directory Path
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
    // Add more conditions for other extensions as needed
    else fileType = "[OTHER FILE]";

    // Truncate the string to a maximum length of 15 characters
    if (fileType.length() > 15) {
        fileType = fileType.substr(0, 12) + "...";
    }

    return fileType;
}

// Function to list current directory contents
void listCurrentDirectory(const fs::path& currentPath) {
    try {
        // Column headers
        std::cout << std::left 
                  << std::setw(15) << "Type" 
                  << std::setw(25) << "Name" 
                  << std::setw(15) << "Size" 
                  << std::endl;
        std::cout << std::string(80, '-') << std::endl;

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
        return currentPath.parent_path(); // Go up to the parent directory
    } else if (input == ".") {
        // List subdirectories and let the user choose one to go down
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
            return newPath; // Return the new path if it exists and is a directory
        } else {
            std::cerr << "Error: Directory not found. Please note that spelling and case must be exact." << std::endl;
            return currentPath; // Stay in the current directory
        }
    } else {
        fs::path newPath = currentPath / input;
        if (fs::exists(newPath) && fs::is_directory(newPath)) {
            return newPath; // Return the new path if it exists and is a directory
        } else {
            std::cerr << "Error: Directory not found. Please note that spelling and case must be exact." << std::endl;
            return currentPath; // Stay in the current directory
        }
    }
}

// Rename File
void renameFile(const fs::path& currentPath) {
    system(CLEAR_COMMAND);
    printBorder("RENAME FILE");
    displayCurrentDirectory(currentPath);
    listCurrentDirectory(currentPath);
    std::cout << std::endl;

    std::string oldName, newName;
    std::cout << ">>>>> Enter the current file name: ";
    std::getline(std::cin, oldName);
    std::cout << ">>>>> Enter the new file name: ";
    std::getline(std::cin, newName);

    try {
        fs::rename(currentPath / oldName, currentPath / newName);
        std::cout << "File renamed successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error renaming file: " << e.what() << std::endl;
    }
}

// Delete File
void deleteFile(const fs::path& currentPath) {
    system(CLEAR_COMMAND);
    printBorder("DELETE FILE");
    displayCurrentDirectory(currentPath);
    listCurrentDirectory(currentPath);
    std::cout << std::endl;

    std::string fileName;
    std::cout << ">>>>> Enter the file name to delete: ";
    std::getline(std::cin, fileName);

    try {
        if (fs::remove(currentPath / fileName)) {
            std::cout << "File deleted successfully." << std::endl;
        } else {
            std::cerr << "File not found." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error deleting file: " << e.what() << std::endl;
    }
}

// Copy File or Directory
void copyFileOrDir(const fs::path& currentPath) {
    system(CLEAR_COMMAND);
    printBorder("COPY FILE");
    displayCurrentDirectory(currentPath);
    listCurrentDirectory(currentPath);
    std::cout << std::endl;

    std::string source, destination;
    std::cout << ">>>>> Enter the source path (file or directory): ";
    std::getline(std::cin, source);
    std::cout << ">>>>> Enter the destination path: ";
    std::getline(std::cin, destination);

    try {
        fs::copy(currentPath / source, destination, fs::copy_options::overwrite_existing | fs::copy_options::recursive);
        std::cout << "Copied successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error copying: " << e.what() << std::endl;
    }
}

// Move File or Directory
void moveFile(const fs::path& currentPath) {
    system(CLEAR_COMMAND);
    printBorder("MOVE FILE");
    displayCurrentDirectory(currentPath);
    listCurrentDirectory(currentPath);
    std::cout << std::endl;

    std::string source, destination;
    std::cout << ">>>>> Enter the source file name: ";
    std::getline(std::cin, source);
    std::cout << ">>>>> Enter the destination path: ";
    std::getline(std::cin, destination);

    try {
        fs::rename(currentPath / source, destination);
        std::cout << "File moved successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error moving file: " << e.what() << std::endl;
    }
}

// Re-order Files by Name
void reorderFiles(const fs::path& currentPath) {
    system(CLEAR_COMMAND);
    printBorder("REORDER FILES");
    displayCurrentDirectory(currentPath);
    listCurrentDirectory(currentPath);
    std::cout << std::endl;
    try {
        std::vector<fs::path> files;
        for (const auto& entry : fs::directory_iterator(currentPath)) {
            if (fs::is_regular_file(entry)) {
                files.push_back(entry.path());
            }
        }
        std::sort(files.begin(), files.end());

        std::cout << "Files in sorted order:\n";
        for (const auto& file : files) {
            std::cout << file.filename() << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error reading directory: " << e.what() << std::endl;
    }
}

// Display Menu and Get User Choice
void printFileOrganiserMenu() {
    printBorder("WHAT DO YOU WANT TO DO?");
    std::cout << "1. Rename File\n"
              << "2. Delete File\n"
              << "3. Copy File\n"
              << "4. Move File\n"
              << "5. Reorder Files\n"
              << "6. Back to main menu" << std::endl;
}

// Main File Organiser Application Function
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

        // Add option to navigate directories
        std::cout << ">>>>> Enter 'navigate' to change directory, or choose an option: ";
        
        std::string userInput;
        std::getline(std::cin, userInput);

        if (userInput == "navigate") {
            currentPath = navigateToDirectory(currentPath);
            continue; // Refresh the loop to display the new directory contents
        }

        int choice;
        try {
            choice = std::stoi(userInput); // Convert string input to int
        } catch (...) {
            std::cout << "Invalid choice. Please enter a number or 'navigate'." << std::endl;
            system("pause");
            continue; // Go back to the start of the loop
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
                moveFile(currentPath);
                break;
            case 5:
                reorderFiles(currentPath);
                break;
            case 6:
                std::cout << "Exiting the application." << std::endl;
                return;
        }
        system("pause"); // Wait for user input before continuing
    }
}
