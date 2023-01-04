#include <cmath>

#include "userInfo.h"
#include "utils.cpp"

User::User()
{
    this->name = "";
    this->balance = -1;
}

User::User(const std::string &name, const double &balance)
{
    this->name = name;
    this->balance = balance;
}

void User::UpdateBalance(const int &balance)
{
    int temp = this->balance;

    this->balance += balance;

    if (!User::saveChanges(this->balance))
    {
        this->balance = temp;
    };
}

bool User::saveChanges(int balance)
{
    std::vector<std::string> users;
    std::fstream file;

    file.open("users.txt", std::ios::in);
    if (file.fail())
    {
        std::cout << "Error: Cannot save changes! Task terminated.";
        return false;
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

        if (currentName == this->name)
        {
            while (currentUser[++i] != ':')
                ;
            currentUser.erase(i + 1);
            currentUser += intToString(balance);
        }
        users.push_back(currentUser);
    }
    file.close();

    file.open("users.txt", std::ios::out);
    if (file.fail())
    {
        std::cout << "Error: Cannot save changes! Task terminated.";
        return false;
    }

    for (int i = 0; i < users.size(); ++i)
    {
        file << users[i] << '\n';
    }
    file.close();

    std::cout << "Successful task.\n"
              << std::endl;
    return true;
}