#include "utils.h"

#include "userInfo.h"
#include "constants.h"

#include <iostream>
#include <fstream>
#include <string>
#include <limits>

std::string intToString(int balance)
{
    std::string res;
    bool isNegative = false;

    if (balance < 0)
    {
        isNegative = true;
        res += '-';
        balance *= -1;
    }

    if (balance == 0)
    {
        return "0";
    }

    while (balance)
    {
        res += balance % 10 + '0';
        balance /= 10;
    }
    int size = res.size();

    for (int i = isNegative; i < size / 2; ++i)
    {
        char temp = res[i];
        res[i] = res[size - i - 1 + isNegative];
        res[size - i - 1 + isNegative] = temp;
    }
    return res;
}

int absUtil(const int &num)
{
    return num < 0 ? num * -1 : num;
}

User getUserInfo(std::fstream &file, const std::string &name, const std::size_t &hash)
{
    long balance = 0; // saved in the smallest currency unit, in this case cents
    unsigned short size = 0;
    std::string currentUser;

    while (std::getline(file, currentUser))
    {
        int i = 0;
        std::string strBalance;
        std::string currentName;
        std::size_t currentHash = 0;
        bool isNegative = false;

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
        ++i;

        if (currentName != name)
        {
            continue;
        }

        if (currentHash != hash && hash != -1)
        {
            continue;
        }

        if (currentUser[i] == '-')
        {
            isNegative = true;
            ++i;
        }

        while (currentUser[i] != '\0' && i < currentUser.size())
        {
            balance = balance * 10 + currentUser[i] - '0';
            ++i;
        }

        balance = isNegative ? balance * -1 : balance;
        User user(name, balance, hash);

        file.close();
        return user;
    }
    User nullUser;

    file.close();
    return nullUser;
};

bool doesUserExists(std::fstream &file, const std::string &name, const std::size_t &hash)
{
    return (!getUserInfo(file, name, hash).name.empty());
}

bool takeUserInput(std::string &name, std::string &password)
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter Full Name: ";
    std::getline(std::cin, name);

    std::cout << "Enter Password: ";
    std::getline(std::cin, password);

    std::cout << std::endl;

    return (!std::cin.fail() && isInputValid(name, password));
}

bool isNameValid(const std::string &name)
{
    unsigned short spaces = 0;
    unsigned short upperCaseLetters = 0;
    unsigned short firstNameLen = 0;
    unsigned short surNameLen = 0;

    for (unsigned short i = 0; i < name.size(); ++i)
    {
        // if letter is uppercase && first in name sequence
        if ((name[i] - 'A' >= 0 && name[i] - 'A' <= 26) && (i == 0 || name[i - 1] == ' '))
        {
            ++upperCaseLetters;
            if (spaces == 0)
            {
                ++firstNameLen;
            }
            if (spaces == 1)
            {
                ++surNameLen;
            }
        }
        else if (name[i] == ' ')
        {
            ++spaces;
        }
        else if (name[i] - 'a' >= 0 && name[i] - 'a' <= 26)
        {
            if (spaces == 0)
            {
                ++firstNameLen;
            }
            if (spaces == 1)
            {
                ++surNameLen;
            }
            continue;
        }
        else
        {
            return false;
        }
    }
    return (spaces == 1 && upperCaseLetters == 2 &&
            firstNameLen >= constantsInit::MIN_LEN_NAME &&
            firstNameLen <= constantsInit::MAX_LEN_NAME &&
            surNameLen >= constantsInit::MIN_LEN_NAME &&
            surNameLen <= constantsInit::MAX_LEN_NAME);
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
                if (password[i] == constantsInit::ALLOWED_SPECIAL_CHARS[j])
                {
                    hasSpecialCharacter = true;
                }
            }
        }
    }

    return (hasUpperCase && hasLowerCase && hasNumber && hasSpecialCharacter);
}

bool isInputValid(const std::string &name, const std::string &password)
{
    if (!isNameValid(name))
    {
        std::cout << "\n\n\033[47m\033[30;1mError:\033[0m Insufficient Name" << std::endl;
        std::cout << "\tGuide: The name should consist only of latin characters [A-Z a-z] and be in the form of <FirstName Surname>" << std::endl;
        return false;
    }

    if (!isPasswordValid(password))
    {
        std::cout << "\n\033[47m\033[30;1mError:\033[0m  Insufficient Password" << std::endl;
        std::cout << "\tGuide: Password should consist of latin letters [A-Z a-z], numbers [0-9] and symbols [! @ # $ % ^ & *]" << std::endl;
        std::cout << "\tRequirements: At least 1 lowercase Letter, 1 uppercase letter and 1 symbol\n\tPassword length should be in the range [5, 20]." << std::endl;
        return false;
    }
    return true;
}