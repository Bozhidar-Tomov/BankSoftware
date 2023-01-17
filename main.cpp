#include "onStart.h"
#include "constants.h"

#include <iostream>

int main(void)
{
    // make system call to enable ANSI support on Windows terminal. ANSI supported on other platforms
    system("");
    std::cout << " ============================================== " << std::endl;
    std::cout << "|   Course project - No9    \033[1m\033[37;1m~ BANK SOFTWARE ~\033[0m  |" << std::endl;
    std::cout << "|    Author - Bozhidar Tomov - 0MI0600171      |" << std::endl;
    std::cout << "|           Year 1, Winter Semester            |" << std::endl;
    std::cout << "|                     2023                     |" << std::endl;
    std::cout << " ============================================== " << std::endl;
    std::cout << std::endl;
    displayOptions();

    while (true)
    {
        char input = '\0';
        std::cin >> input;

        switch (input)
        {
        case constantsInit::LOGIN:
            std::cout << "Login selected" << std::endl;
            login();
            break;
        case constantsInit::REGISTER:
            std::cout << "Register selected" << std::endl;
            registerNewUser();
            break;
        case constantsInit::QUIT:
            break;

        default:
            std::cout << "Invalid Input." << std::endl;
            displayOptions();
            continue;
        }
        std::cout << "Press any key to close...";
        std::getchar();
        break;
    }
    return 0;
}