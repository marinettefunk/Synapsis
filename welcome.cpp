#include <iostream>
#include "formatting.h"

void printLogo() {
    std::cout << "█████╗  ██╗ ██╗  ██████╗  ██████╗  ██████╗  █████╗  ██╗  █████╗\n";
    std::cout << "██═══╝  ██║ ██║  ██║ ██║  ██║ ██║  ██║ ██║  ██═══╝  ██║  ██═══╝\n";
    std::cout << "█████╗  ██████╝  ██║ ██║  ██████║  ██████╝  █████╗  ██║  █████╗\n";
    std::cout << "   ██║    ██║    ██║ ██║  ██║ ██║  ██║         ██║  ██║     ██║\n";
    std::cout << "█████║    ██║    ██║ ██║  ██║ ██║  ██║      █████║  ██║  █████║\n";
    std::cout << "╚════╝    ╚═╝    ╚═╝ ╚═╝  ╚═╝ ╚═╝  ╚═╝      ╚════╝  ╚═╝  ╚════╝\n";
}

void message() {
    fadeIn("HELLO, I'M");
    printLogo();
    fadeIn("YOUR VIRTUAL ASSISTANT");
    std::cout << std::endl;
}