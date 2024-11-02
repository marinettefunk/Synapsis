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

#ifndef PROFILE_H
#define PROFILE_H

#include <string>

// Function to save user data to a file.
void saveUserData(const std::string& name, const std::string& password);

// Function to load user data from a file.
void loadUserData(std::string& name, std::string& password);

// Function to get the user's name.
std::string getName();

// Function to confirm the user's name.
void nameConfirmation(std::string& name);

// Function to get and confirm the user's password.
std::string getPassword();

// Function to create a profile when program is first run.
void createProfile(std::string& name, std::string& password);

// Function on program start based on user data.
std::string runProgram();

// Function to display the Profile Settings Menu.
void printProfileSettingsMenu();

// Function to display the user's profile.
void viewProfile(const std::string& name, const std::string& password);

// Function to change the name of the user.
void changeName(std::string& name, std::string& password);

// Function to change the user's password.
void changePassword(std::string& password, std::string& name);

// Function to delete the user's profile.
void deleteProfile(std::string& name, std::string& password);

// Main function to handle profile settings menu.
void profileSettings(std::string& name, std::string& password);

#endif  // PROFILE_H