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
#include "welcome.h"
#include "profile.h"
#include "menu.h"

using namespace std;

int main() {
    // Display welcome message.
    message();

    // Login and profile handling.
    std::string name = runProgram();

    // Main menu and function execution.
    printMenu(name);
    
    return 0;
}