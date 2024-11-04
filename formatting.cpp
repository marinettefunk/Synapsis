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
#include <iomanip>
#include <string>
#include <chrono>
#include <thread>

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif

// Function to get the width of the console window.
int getConsoleWidth() {
    #if defined(_WIN32) || defined(_WIN64)
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        // Retrieve console screen buffer information.
        if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
            return csbi.srWindow.Right - csbi.srWindow.Left + 1;
        }
    #else
        struct winsize w;
        // Use ioctl to get window size on Unix-like systems.
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
            return w.ws_col;
        }
    #endif
    // Default width if unable to detect.
    return 80;
}

// Fuction to apply fade-in effect on text.
std::string fadeIn(const std::string& text) {
    // Print line with each character gradually appearing
    for (size_t i = 0; i < text.length(); ++i) {
        std::cout << text[i] << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Adjust for speed
    }
    std::cout << std::endl;
    return text; // Return the original text
}

//Function to apply a border to text.
void printBorder(const std::string& message) {
    int length = message.length();

    // Print top border with corners
    std::cout << "╭";
    for (int i = 0; i < length + 2; ++i) {
        std::cout << "─";
    }
    std::cout << "╮" << std::endl;

    // Print message with side borders
    std::cout << "│ " << message << " │" << std::endl;

    // Print bottom border with corners
    std::cout << "╰";
    for (int i = 0; i < length + 2; ++i) {
        std::cout << "─";
    }
    std::cout << "╯" << std::endl;
}

//Function to get the local time.
void dateTime() {
    // Declaring argument for time().
    time_t tt;

    // Declaring variable to store return value of localtime(). 
    struct tm* ti;

    // Applying time(). 
    time(&tt);

    // Using localtime(). 
    ti = localtime(&tt);

    // Get the length of the date and time string.
    std::string dateTimeStr = asctime(ti);

    // Get the console width.
    int consoleWidth = getConsoleWidth();

    // Print the date and time, aligned to the right.
    std::cout << std::setw(consoleWidth) << std::right << dateTimeStr;
}

// Utility function to pause and wait for user input before returning to the menu.
void pauseForReturn() {
    std::cout << "\n>>>>> Press Enter to return to the menu <<<<<<";
    std::cin.ignore(10000, '\n');
}