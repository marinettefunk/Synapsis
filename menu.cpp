#include <iostream>
#include <vector>
#include <string>
#include "formatting.h"

// Function to print the table
void printTable(const std::vector<std::vector<std::string>>& data) {
    centerText( "CHOOSE AN OPTION"); // Column numbers
    std::cout << "----------------------------------------\n"; // Adjusted separator

    for (const auto& row : data) {
        for (const auto& item : row) {
            std::cout << item << "\t\t"; // Print each item in the row
        }
        std::cout << std::endl; // Move to the next line after each row
    }
}


// Function to run the table display
void runTableDisplay() {
    // Data for the table, with a single row of items
    std::vector<std::vector<std::string>> tableData = {
        {"1. Profile Settings", "2. File Organizer", "3. Weather App", "4.Calculator"},
    };

    printTable(tableData); // Call the function to print the table
}