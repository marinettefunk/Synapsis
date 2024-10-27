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
    smoothFadeInLine("HELLO, I'M");
    printLogo();
    smoothFadeInLine("YOUR VIRTUAL ASSISTANT");
    std::cout << std::endl;
}