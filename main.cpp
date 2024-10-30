#include <iostream>
#include "welcome.h"
#include "profile.h"
#include "menu.h"

using namespace std;

int main() {
    message();
    std::string name = runProgram();
    printMenu(name);
    return 0;
}