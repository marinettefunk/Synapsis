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

#ifndef FORMATTING_H
#define FORMATTING_H

#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <iomanip>

// Function to get the width of the console window.
int getConsoleWidth();

// Function to apply fade-in effect on text.
std::string fadeIn(const std::string& text);

// Function to apply a border to text.
void printBorder(const std::string& message);

// Function to get the local time.
void dateTime();

// Utility function to pause and wait for user input before returning to the menu.
void pauseForReturn();

#endif  // FORMATTING_H