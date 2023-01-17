#include "onStart.h"

#include "utils.h"
#include "userInfo.h"
#include "accountOperations.h"
#include "constants.h"

#include <iostream>
#include <fstream>

void registerNewUser(void)
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
    if (!file)
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
        if (!file)
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

void login(void)
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
    if (!file)
    {
        std::cout << "\033[31mError:\033[0m " << constantsInit::FILE_NAME << " file does not exist.";

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

void displayOptions(void)
{
    std::cout << "\033[4m Choose an option: \033[0m" << std::endl;
    std::cout << "\033[33mL\033[0m --> Login" << std::endl;
    std::cout << "\033[33mR\033[0m --> Register" << std::endl;
    std::cout << "\033[33mQ\033[0m --> Quit" << std::endl;
    return;
}