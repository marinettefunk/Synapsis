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
    dateTime();
    fadeIn("HELLO, I'M");
    printLogo();
    fadeIn("YOUR VIRTUAL ASSISTANT");
    std::cout << std::endl;
}