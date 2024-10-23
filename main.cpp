#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "welcome.h"
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

int main() {

    lines(getConsoleWidth());

    return 0;
}