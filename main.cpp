#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <vector>
#include "constants.h"
#include "userInfo.cpp"

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
            return false;
        }
    }

    if (!(spaces == 1 && upperCaseLetters == 2))
    {
        return false;
    }
    return true;
}

bool isPasswordValid(const std::string &password)
{

    bool hasUpperCase = false;
    bool hasLowerCase = false;
    bool hasNumber = false;
    bool hasSpecialCharacter = false;

    if (password.size() < constantsInit::MIN_LEN_PASSWORD && password.size() > constantsInit::MAX_LEN_PASSWORD)
    {
        return false;
    }

    for (unsigned short i = 0; i < password.size(); ++i)
    {
        if (password[i] - 'a' <= 26 && password[i] - 'a' >= 0)
        {
            hasLowerCase = true;
        }
        else if (password[i] - 'A' <= 26 && password[i] - 'A' >= 0)
        {
            hasUpperCase = true;
        }
        else if (password[i] - '0' <= 9 && password[i] - '0' >= 0)
        {
            hasNumber = true;
        }
        else
        {
            for (unsigned short j = 0; j < 8; ++j)
            {
                if (password[i] == constantsInit::allowedSpecialCharacters[j])
                {
                    hasSpecialCharacter = true;
                }
            }
        }
    }

    if (!(hasUpperCase && hasLowerCase && hasNumber && hasSpecialCharacter))
    {
        return false;
    }
    return true;
}

bool isInputValid(const std::string &name, const std::string &password)
{
    if (!isNameValid(name))
    {
        std::cout << "\n\n\u001b[47m\u001b[30;1mError:\u001b[0m Insufficient Name" << std::endl;
        std::cout << "\tGuide: The name should consist only of latin characters [A-Z a-z] and be in the form of <FirstName Surname>" << std::endl;
        return false;
    }

    if (!isPasswordValid(password))
    {
        std::cout << "\n\u001b[47m\u001b[30;1mError:\u001b[0m  Insufficient Password" << std::endl;
        std::cout << "\tGuide: Password should consist of latin letters [A-Z a-z], numbers [0-9] and symbols [! @ # $ % ^ & *]" << std::endl;
        std::cout << "\tRequirements: At least 1 lowercase Letter, 1 uppercase letter and 1 symbol\n\tPassword length should be in the range [5, 20]." << std::endl;
        return false;
    }
    return true;
}

void cancelAccount(User &user)
{
    std::fstream file;
    std::vector<std::string> users;

    file.open(constantsInit::FILE_NAME, std::ios::in);
    if (file.fail())
    {
        std::cout << "Error: Cannot open file " << constantsInit::FILE_NAME << " ! Task terminated" << std::endl;
        return;
    }

    std::string currentUser;

    while (std::getline(file, currentUser))
    {
        int i = 0;
        std::string currentName;

        while (currentUser[i] != ':')
        {
            currentName += currentUser[i++];
        }

        if (currentName != user.name)
        {
            users.push_back(currentUser);
        }
    }
    file.close();

    file.open(constantsInit::FILE_NAME, std::ios::out);
    if (file.fail())
    {
        std::cout << "Error: Cannot open file " << constantsInit::FILE_NAME << " ! Task terminated" << std::endl;
        return;
    }

    for (int i = 0; i < users.size(); ++i)
    {
        file << users[i] << '\n';
    }
    file.close();

    std::cout << "Successful task.\n"
              << std::endl;
    return;
}

void displayAccountOptions()
{
    std::cout << "\u001b[4m Choose an option: \u001b[0m" << std::endl;
    std::cout << "\u001b[31mC\u001b[0m --> Cancel account" << std::endl;
    std::cout << "\u001b[36mD\u001b[0m --> Deposit" << std::endl;
    std::cout << "\u001b[36mL\u001b[0m --> Logout" << std::endl;
    std::cout << "\u001b[36mT\u001b[0m --> Transfer" << std::endl;
    std::cout << "\u001b[36mW\u001b[0m --> Withdraw" << std::endl;
    return;
}

void deposit(User &user)
{
    double amount = 0;
    std::cout << "Enter deposit amount: ";
    std::cin >> amount;

    if (std::cin.fail())
    {
        std::cout << "Error: Invalid input data! Task terminated";
        return;
    }
    user.UpdateBalance((int)(amount * constantsAccount::ROUND_PRECISION));
};

void transfer(){};

void withdraw(){};

void account(User &user)
{
    std::cout << "\nWelcome back, " << user.name << std::endl;

    while (true)
    {
        std::cout << "You have \033[32;1m " << (double)user.balance / constantsAccount::ROUND_PRECISION << " BGN\033[0m.\n"
                  << std::endl;

        displayAccountOptions();

        char input = '\0';
        std::cin >> input;

        switch (input)
        {
        case constantsAccount::Cancel:
            std::cout << "Cancel selected" << std::endl;
            cancelAccount(user);
            break;
        case constantsAccount::Deposit:
            std::cout << "Deposit selected" << std::endl;
            deposit(user);
            continue;
        case constantsAccount::Logout:
            std::cout << "Logout selected" << std::endl;
            break;
        case constantsAccount::Transfer:
            std::cout << "Transfer selected" << std::endl;
            continue;
        case constantsAccount::Withdraw:
            std::cout << "Withdraw selected" << std::endl;
            continue;

        default:
            std::cout << "Invalid Input." << std::endl;
            continue;
        }
        break;
    }
}

User getUserInfo(std::fstream &file, const std::string &name, const std::size_t &hash)
{
    int balance = 0; // saved in the smallest currency unit, in this case cents
    unsigned short size = 0;
    std::string currentUser;

    while (std::getline(file, currentUser))
    {
        int i = 0;
        std::string strBalance;
        std::string currentName;
        std::size_t currentHash = 0;

        while (currentUser[i] != ':' && i < currentUser.size())
        {
            currentName += currentUser[i];
            ++i;
        }
        ++i;
        while (currentUser[i] != ':' && i < currentUser.size())
        {
            currentHash = currentHash * 10 + currentUser[i] - '0';
            ++i;
        }

        if (currentHash != hash || currentName != name)
        {
            continue;
        }
        ++i;

        while (currentUser[i] != '\0' && i < currentUser.size())
        {
            balance = balance * 10 + currentUser[i] - '0';
            ++i;
        }

        User user(name, balance);
        return user;
    }

    file.close();
    User nullUser;
    return nullUser;
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

    file.open(constantsInit::FILE_NAME, std::ios::in);
    if (!file)
    {
        char input = '\n';

        std::cout << "\u001b[33;1mWarning:\u001b[0m " << constantsInit::FILE_NAME << " file does not exist.\nDo you want to create " << constantsInit::FILE_NAME << " and continue? [y,N] ";
        std::cin >> input;

        if (input == constantsInit::Yes)
        {
            file.open(constantsInit::FILE_NAME, std::ios::out);
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

    if (!getUserInfo(file, name, hash).name.empty())
    {
        std::cout << "\u001b[33;1mWarning:\u001b[0m User already exists! Task terminated." << std::endl;
        return;
    }
    file.close();
    file.open(constantsInit::FILE_NAME, std::ios::app);
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

    file.open(constantsInit::FILE_NAME, std::ios::in);
    if (!file)
    {
        std::cout << "\u001b[31;1mError:\u001b[0m " << constantsInit::FILE_NAME << " file does not exist.";
        exit(EXIT_FAILURE);
    }

    User user = getUserInfo(file, name, hash);

    if (user.name.empty())
    {
        std::cout << "User not found." << std::endl;
        return;
    }
    account(user);
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
        case constantsInit::Login:
            std::cout << "login selected" << std::endl;
            login();
            break;
        case constantsInit::Register:
            std::cout << "register selected" << std::endl;
            registerNewUser();
            break;
        case constantsInit::Quit:
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