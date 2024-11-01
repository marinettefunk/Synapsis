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