#ifndef FORMATTING_H
#define FORMATTING_H

#include <string>

int getConsoleWidth();
void centerText(const std::string& text);
std::string getCenteredText(const std::string& text);
void fadeIn(const std::string& text);
void printBorder(const std::string& message);
void dateTime();

#endif // FORMATTING_H