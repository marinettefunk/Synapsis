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

    std::cout << std::string(padding, ' ') << text << std::endl;
}
void smoothFadeInLine(const std::string& text) {
    // Print line with each character gradually appearing
    for (size_t i = 0; i < text.length(); ++i) {
        std::cout << text[i] << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Adjust for speed
    }
    std::cout << std::endl;
}

void printLogo() {
    std::cout << "█████  ██  ██  ██████  ██████  ██████  █████  ██  █████\n";
    std::cout << "██     ██  ██  ██  ██  ██  ██  ██  ██  ██     ██  ██ \n";
    std::cout << "█████  ██████  ██  ██  ██████  ██████  █████  ██  █████\n";
    std::cout << "   ██    ██    ██  ██  ██  ██  ██         ██  ██     ██\n";
    std::cout << "█████    ██    ██  ██  ██  ██  ██      █████  ██  █████\n";
}

void message() {
    smoothFadeInLine("HELLO, I'M");
    printLogo();
    smoothFadeInLine("YOUR VIRTUAL ASSISTANT");
    std::cout << std::endl;
    centerText("What can I help you with?");
    
}
