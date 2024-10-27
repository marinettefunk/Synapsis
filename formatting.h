#ifndef FORMATTING_H
#define FORMATTING_H

#include <string>

int getConsoleWidth();
void centerText(const std::string& text);
void smoothFadeInLine(const std::string& text);
void printWithModernBorder(const std::string& message);

#endif // FORMATTING_H