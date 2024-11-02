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

#ifndef CHAT_H
#define CHAT_H

#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>
#include <ctime>
#include "formatting.h"
#include "welcome.h"
#include "menu.h"
#include "profile.h"
#include "files.h"

// URL Encoding and Web Search Functions
std::string urlEncode(const std::string& query);  // Encodes a query string for URL use.
void googleSearch(const std::string& query);      // Performs a Google search with the given query.
void youtubeSearch(const std::string& query);     // Performs a YouTube search with the given query.
void spotifySearch(const std::string& query);     // Performs a Spotify search with the given query.
void wikipediaSearch(const std::string& query);   // Performs a Wikipedia search with the given query.

// Social Media Functions.
void openWhatsApp();      // Opens WhatsApp.
void openInstagram();     // Opens Instagram.
void openFacebook();      // Opens Facebook.
void openLinkedIn();      // Opens LinkedIn.

// Chatbot Functions.
std::string handleUserInput(const std::string& userInput);  // Handles user input and generates a response.
void ChatBot();     // Main ChatBot function.

#endif // CHAT_H