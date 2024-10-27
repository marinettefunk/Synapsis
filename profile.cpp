#include <iostream>
#include <string>

#include <iostream>
#include <string>

std::string getName() {
    std::string name;
    std::cout << "Please enter your name: ";
    std::getline(std::cin, name);
    return name;
}

void nameConfirmation(){
    std::string name = getName(); // Call getName() once and store the result
    char confirm = '\0'; // Initialize with a default value

    do {
        std::cout << "Your name is " << name << ". Is this correct? (y/n): ";
        std::cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            break;
        } else if (confirm == 'n' || confirm == 'N') {
            name = getName(); // Call getName() again if the user wants to change their name
        } else {
            std::cout << "Invalid input. Please enter 'y' or 'n'." << std::endl;
        }
    } while (true);
}

std::string getPassword() {
    std::string password;
    std::string confirmPassword;

    std::cout << "Please enter your password: ";
    std::cin.ignore(); // ignore the newline character
    std::getline(std::cin, password);

    do {
        std::cout << "Re-enter your password: ";
        std::getline(std::cin, confirmPassword);

        if (password != confirmPassword) {
            std::cout << "Passwords do not match. Please try again." << std::endl;
        }
    } while (password != confirmPassword);

    return password;
}

void printProfile() {
    std::cout << "FIRST, LET'S CREATE YOUR PROFILE" << std::endl;
    nameConfirmation();
    getPassword();
}