#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include "constants.h"

bool checkUser(const std::string name, const std::size_t &hash, const std::string &currentUser)
{
    int i = 0;
    std::size_t currentHash = 0;

    while (currentUser[i] != ':')
    {
        if (currentUser[i] != name[i])
        {
            return 0;
        }
        ++i;
    }
    ++i;

    while (currentUser[i] != ':')
    {
        currentHash = currentHash * 10 + currentUser[i] - '0';
        ++i;
    }

    if (currentHash != hash)
    {
        return 0;
    }

    return 1;
}

bool isNameValid(const std::string &name)
{
    unsigned short spaces = 0;
    unsigned short upperCaseLetters = 0;
    for (unsigned short i = 0; i < name.size(); ++i)
    {
        if ((name[i] - 'A' >= 0 && name[i] - 'A' <= 26) && (i == 0 || name[i - 1] == ' '))
        {
            ++upperCaseLetters;
        }
        else if (name[i] == ' ')
        {
            ++spaces;
        }

        else if (name[i] - 'a' < 0 || name[i] - 'a' > 26)
        {
            return 0;
        }
    }

    if (spaces == 1 && upperCaseLetters == 2)
    {
        return 1;
    }
    return 0;
}

bool isPasswordValid(const std::string &password)
{

    bool hasUpperCase = 0;
    bool hasLowerCase = 0;
    bool hasNumber = 0;
    bool hasSpecialCharacter = 0;

    if (password.size() < 5 && password.size() > 20)
    {
        return 0;
    }

    for (unsigned short i = 0; i < password.size(); ++i)
    {
        if (password[i] - 'a' <= 26 && password[i] - 'a' >= 0)
        {
            hasLowerCase = 1;
        }
        else if (password[i] - 'A' <= 26 && password[i] - 'A' >= 0)
        {
            hasUpperCase = 1;
        }
        else if (password[i] - '0' <= 9 && password[i] - '0' >= 0)
        {
            hasNumber = 1;
        }
        else
        {
            for (unsigned short j = 0; j < 8; ++j)
            {
                if (password[i] == constants::allowedSpecialCharacters[j])
                {
                    hasSpecialCharacter = 1;
                }
            }
        }
    }

    if (!(hasUpperCase && hasLowerCase && hasNumber && hasSpecialCharacter))
    {
        return 0;
    }
    return 1;
}

bool isInputValid(const std::string &name, const std::string &password)
{
    if (!isNameValid(name))
    {
        std::cout << "\n\n\u001b[47m\u001b[30;1mError:\u001b[0m Insufficient Name" << std::endl;
        std::cout << "\tGuide: The name should consist only of latin characters [A-Z a-z] and be in the form of <FirstName Surname>" << std::endl;
        return 0;
    }

    if (!isPasswordValid(password))
    {
        std::cout << "\n\u001b[47m\u001b[30;1mError:\u001b[0m  Insufficient Password" << std::endl;
        std::cout << "\tGuide: Password should consist of latin letters [A-Z a-z], numbers [0-9] and symbols [! @ # $ % ^ & *]" << std::endl;
        std::cout << "\tRequirements: At least 1 lowercase Letter, 1 uppercase letter and 1 symbol\nPassword length should be in the range [5, 20]." << std::endl;
        return 0;
    }
    return 1;
}

bool doesUserExist(std::fstream &file, const std::string &name, const std::size_t &hash)
{
    std::string currentUser;
    while (std::getline(file, currentUser))
    {
        if (checkUser(name, hash, currentUser))
        {
            file.close();
            return 1;
        }
    }
    file.close();
    return 0;
};

void registerNewUser()
{
    std::string name;
    std::string password;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter Full Name: ";
    std::getline(std::cin, name);

    std::cout << "Enter Password: ";
    std::getline(std::cin, password);

    if (!isInputValid(name, password))
    {
        return;
    }

    std::fstream file;
    size_t hash = std::hash<std::string>{}(password);

    file.open("users.txt", std::ios::in);
    if (!file)
    {
        char input = '\n';

        std::cout << "\u001b[33;1mWarning:\u001b[0m users.txt file does not exist.\nDo you want to create users.txt and continue? [y,N] ";
        std::cin >> input;

        if (input == constants::Yes)
        {
            file.open("users.txt", std::ios::out);
            if (!file)
            {
                std::cout << "Error: Cannot create file! Task terminated.";
                file.close();
                exit(EXIT_FAILURE);
            }
            file << name << ":" << hash << ":" << 0 << "\n";
            file.close();
            return;
        }
        else
        {
            std::cout << "Task terminated!" << std::endl;
            file.close();
            return;
        }
    }

    if (doesUserExist(file, name, hash))
    {
        std::cout << "\u001b[33;1mWarning:\u001b[0m User already exists! Task terminated." << std::endl;
        return;
    }

    file.open("users.txt", std::ios::app);
    file << name << ":" << hash << ":" << 0 << "\n";
    file.close();
    std::cout << "success" << std::endl;
    return;
}

void login()
{
    std::string name;
    std::string password;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter Full Name: ";
    std::getline(std::cin, name);

    std::cout << "Enter Password: ";
    std::getline(std::cin, password);

    if (!isInputValid(name, password))
    {
        return;
    }

    std::fstream file;
    size_t hash = std::hash<std::string>{}(password);

    file.open("users.txt", std::ios::in);
    if (!file)
    {
        std::cout << "\u001b[33;1mWarning:\u001b[0m users.txt file does not exist.\nDo you want to create users.txt and continue? [y,N] ";
        return;
    }
    if (doesUserExist(file, name, hash))
    {
        std::cout << "WELCOME!" << std::endl;
        return;
    }

    std::cout << "User not found." << std::endl;
}

void displayOptions()
{
    std::cout << "\u001b[4m Choose an option: \u001b[0m" << std::endl;
    std::cout << "\u001b[33mL\u001b[0m --> Login" << std::endl;
    std::cout << "\u001b[33mR\u001b[0m --> Register" << std::endl;
    std::cout << "\u001b[33mQ\u001b[0m --> Quit" << std::endl;
    return;
}

int main()
{
    std::cout << " ============================================== " << std::endl;
    std::cout << "|   Course project - №9    \u001b[1m\u001b[37;1m~ BANK SOFTWARE ~\u001b[0m   |" << std::endl;
    std::cout << "|    Author - Bozhidar Tomov - 0MI0600171      |" << std::endl;
    std::cout << "|           Year 1, Winter Semester            |" << std::endl;
    std::cout << "|                     2022                     |" << std::endl;
    std::cout << " ============================================== " << std::endl;
    std::cout << std::endl;
    displayOptions();

    while (true)
    {
        char input = '\0';
        std::cin >> input;

        switch (input)
        {
        case constants::Login:
            std::cout << "login selected" << std::endl;
            login();
            break;
        case constants::Register:
            std::cout << "register selected" << std::endl;
            registerNewUser();
            break;
        case constants::Quit:
            std::cout << "quit selected" << std::endl;
            break;

        default:
            std::cout << "Invalid Input." << std::endl;
            displayOptions();
            continue;
        }
        break;
    }
    return 0;
}