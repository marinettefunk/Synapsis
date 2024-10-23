# ifndef WELCOME_H
# define WELCOME_H
#include <string>

void enableANSIForWindows();
std::string getANSIBrightnessCode(int brightness);
void resetColor();
void animateFlashingText(const std::string& text, int fadeInDuration, int consoleWidth);
int getConsoleWidth();
void lines(int consoleWidth);

# endif // WELCOME_H