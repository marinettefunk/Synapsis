
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

int getConsoleWidth() {
#if defined(_WIN32) || defined(_WIN64)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
#else
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
        return w.ws_col;
    }
#endif
    // Default width if unable to detect
    return 80;
}
void centerText(const std::string& text) {
    int width = getConsoleWidth();
    int padding = (width - text.length()) / 2;
    std::cout << std::string(padding, ' ') << text << std::string(width - text.length() - padding, ' ') << std::endl;
}

std::string getCenteredText(const std::string& text) {
    int width = getConsoleWidth();
    int padding = (width - text.length()) / 2;
    return std::string(padding, ' ') + text + std::string(width - text.length() - padding, ' ');
}
void fadeIn(const std::string& text) {
    // Print line with each character gradually appearing
    for (size_t i = 0; i < text.length(); ++i) {
        std::cout << text[i] << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Adjust for speed
    }
    std::cout << std::endl;
}
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

void dateTime() {
    // Declaring argument for time() 
    time_t tt;

    // Declaring variable to store return value of localtime() 
    struct tm* ti;

    // Applying time() 
    time(&tt);

    // Using localtime() 
    ti = localtime(&tt);

    // Get the console width
    int width = getConsoleWidth();

    // Print the date and time, aligned to the right
    std::cout << std::setw(width) << std::right << asctime(ti);
}