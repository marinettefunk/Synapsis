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

#ifndef MENU_H
#define MENU_H

#include <string>

// Input validation when choosing option from Main Menu.
int choice();

// Function to print Main Menu.
void printMenu(const std::string& name);

#endif // MENU_H