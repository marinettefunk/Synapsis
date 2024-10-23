#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Function to enable ANSI escape codes on Windows
void enableANSIForWindows() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }
#endif
}

// Function to generate the ANSI escape code for brightness
std::string getANSIBrightnessCode(int brightness) {
    return "\033[38;5;" + std::to_string(brightness) + "m";
}

// Function to reset the text color
void resetColor() {
    std::cout << "\033[0m";
}

// Function to animate text flashing (fade in only)
void animateFlashingText(const std::string& text, int fadeInDuration, int consoleWidth) {
    int brightnessMin = 232; // Dark gray (almost black) - ANSI 256-color palette
    int brightnessMax = 255; // White - ANSI 256-color palette

    int fadeInSteps = 10; // Number of steps for fading in

    // Calculate leading spaces for centering
    int textLength = text.length();
    int leadingSpaces = (consoleWidth - textLength) / 2;

    // Fade in
    for (int i = 0; i <= fadeInSteps; ++i) {
        int brightness = brightnessMin + (brightnessMax - brightnessMin) * i / fadeInSteps;
        std::cout << getANSIBrightnessCode(brightness) << std::string(leadingSpaces, ' ') << text << "\r" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(fadeInDuration / fadeInSteps));
    }

    // Pause at full brightness
    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    // Reset color and print the final text
    resetColor();
    std::cout << std::string(leadingSpaces, ' ') << text << std::endl; // Keep the text visible
}

// Function to get the console width
int getConsoleWidth() {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1; // Width of the console
#else
    return 80; // Default width for non-Windows (change as needed)
#endif
}

// Flash each line separately and keep it centered
void lines(int consoleWidth) {
    // Enable ANSI support on Windows
    enableANSIForWindows();

    // Get console width (not needed, already passed as a parameter)
    // int consoleWidth = getConsoleWidth();

    std::string lines[] = {
        "WELCOME",
        "I'M SYNAPSIS",
        "YOUR VIRTUAL ASSISTANT"
    };

    for (const auto& line : lines) {
        animateFlashingText(line, 1000, consoleWidth); // Fade in over 1 second
    }
}