#ifndef POFILE_H
#define PROFILE_H
#include <string>

std::string getName();
void nameConfirmation();
std::string getPassword();
void printProfile();
void runProgram();
void viewProfile();
void createProfile();
void changeName();
void changePassword();
void deleteProfile();
void pauseForReturn();
void saveUserData(const std::string& name, const std::string& password);
void loadUserData(std::string& name, std::string& password);
void profileSettings(std::string& name, std::string& password);

#endif // PROFILE_H