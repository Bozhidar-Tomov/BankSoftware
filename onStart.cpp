#include "onStart.h"

#include "utils.h"
#include "userInfo.h"
#include "accountOperations.h"
#include "constants.h"

#include <iostream>
#include <fstream>

static void registerNewUser(void)
{
    std::string name;
    std::string password;

    if (!takeUserInput(name, password))
    {
        return;
    }

    std::fstream file;
    size_t hash = std::hash<std::string>{}(password);

    file.open(constantsInit::FILE_NAME, std::ios::in);
    if (!file.is_open())
    {
        char input = '\0';

        std::cout << "\033[33;1mWarning:\033[0m " << constantsInit::FILE_NAME << " file does not exist.\nDo you want to create " << constantsInit::FILE_NAME << " and continue? [y,N] ";
        std::cin >> input;

        if (input != constantsInit::YES)
        {
            std::cout << "Task terminated!" << std::endl;
            return;
        }

        file.open(constantsInit::FILE_NAME, std::ios::out);
        if (!file.is_open())
        {
            std::cout << "\033[31mError:\033[0m: Cannot create file! Task terminated." << std::endl;
            std::cout << "Press any key to close...";
            std::getchar();
            exit(EXIT_FAILURE);
        }
    }

    if (doesUserExists(file, name, hash))
    {
        std::cout << "\033[33;1mWarning:\033[0m User already exists! Task terminated." << std::endl;
        return;
    }

    User user(name, 0, hash);

    file.open(constantsInit::FILE_NAME, std::ios::app);
    file << name << ":" << hash << ":" << 0 << "\n";
    file.close();

    std::cout << "Account created successfully." << std::endl;
    account(user);
    return;
}

static void login(void)
{
    std::string name;
    std::string password;

    if (!takeUserInput(name, password))
    {
        return;
    }

    std::fstream file;
    size_t hash = std::hash<std::string>{}(password);

    file.open(constantsInit::FILE_NAME, std::ios::in);
    if (!file.is_open())
    {
        std::cout << "\033[31mError:\033[0m " << constantsInit::FILE_NAME << " file does not exist." << std::endl;

        std::cout << "Press any key to close...";
        std::getchar();
        exit(EXIT_FAILURE);
    }

    User user = getUserInfo(file, name, hash);

    if (user.name.empty())
    {
        std::cout << "\033[31mError:\033[0m User not found." << std::endl;
        return;
    }
    account(user);
}

static void displayOptions(void)
{
    std::cout << "\033[4m Choose an option: \033[0m" << std::endl;
    std::cout << "\033[33mL\033[0m --> Login" << std::endl;
    std::cout << "\033[33mR\033[0m --> Register" << std::endl;
    std::cout << "\033[33mQ\033[0m --> Quit" << std::endl;
    return;
}

void run(void)
{
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
    return;
}