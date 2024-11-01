#ifndef FILES_H
#define FILES_H

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

namespace fs = std::filesystem;

// Utility function to format file sizes.
std::string formatFileSize(uintmax_t size);

// Display Current Directory Path.
void displayCurrentDirectory(const fs::path& currentPath);

// Function to get the file type.
std::string getFileType(const fs::path& path);

// Function to list current directory contents.
void listCurrentDirectory(const fs::path& currentPath);

// Function for directory navigation.
fs::path navigateToDirectory(const fs::path& currentPath);

// Rename File function.
void renameFile(const fs::path& currentPath);

// Delete File function.
void deleteFile(const fs::path& currentPath);

// Function to copy file or directory.
void copyFileOrDir(fs::path& currentPath);

// Function to move file or directory.
void moveFileOrDir(fs::path& currentPath);

// Display menu for File Organiser App.
void printFileOrganiserMenu();

// Main File Organiser Application Function.
void fileOrganiserApp();

#endif // FILES_H