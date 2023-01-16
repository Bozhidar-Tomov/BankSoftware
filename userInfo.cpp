#include "userInfo.h"
#include "utils.cpp"

User::User(void)
{
    this->name = "";
    this->balance = -1;
    setHash(-1);
}

User::User(const std::string &name, const long &balance, const size_t &hash)
{
    this->name = name;
    this->balance = balance;
    setHash(hash);
}

bool User::UpdateBalance(const long &balance, const char &type)
{
    int temp = this->balance;

    if (type == constantsAccount::DEPOSIT)
    {
        this->balance += balance;

        if (this->balance > constantsAccount::MAX_BALANCE)
        {
            this->balance = temp;
            std::cout << "Balance max limit of 1,000,000,000.00 exceeded! Task terminated.\n"
                      << std::endl;
            return false;
        }
    }
    else if (type == constantsAccount::WITHDRAW)
    {
        this->balance -= balance;

        if (this->balance < 0 && absUtil(this->balance) > constantsAccount::OVERDRAFT_LIMIT)
        {
            this->balance = temp;
            std::cout << "Overdraft limit of 10,000.00 exceeded! Task terminated.\n"
                      << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "\033[31mUnexpected error has ocurred! Task terminated.\033[0m\n"
                  << std::endl;
        return false;
    }

    if (!User::saveChanges())
    {
        this->balance = temp;
        return false;
    };
    return true;
}

bool User::saveChanges(void)
{
    std::vector<std::string> users;
    std::fstream file;

    file.open(constantsInit::FILE_NAME, std::ios::in);
    if (file.fail())
    {
        std::cout << "\033[31mError:\033[0m Cannot save changes! Task terminated.\n"
                  << std::endl;
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
            currentUser += intToString(this->balance);
        }
        users.push_back(currentUser);
    }
    file.close();

    file.open(constantsInit::FILE_NAME, std::ios::out);
    if (file.fail())
    {
        std::cout << "\033[31mError:\033[0m: Cannot save changes! Task terminated.\n"
                  << std::endl;

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

bool User::cancelAccount(void)
{
    std::fstream file;
    std::vector<std::string> users;

    file.open(constantsInit::FILE_NAME, std::ios::in);
    if (file.fail())
    {
        std::cout << "\033[31mError:\033[0m: Cannot open file " << constantsInit::FILE_NAME << " ! Task terminated" << std::endl;
        return false;
    }

    std::string currentUser;

    while (std::getline(file, currentUser))
    {
        int i = 0;
        std::string currentName;
        std::size_t currentHash = 0;

        while (currentUser[i] != ':')
        {
            currentName += currentUser[i++];
        }

        ++i;
        while (currentUser[i] != ':' && i < currentUser.size())
        {
            currentHash = currentHash * 10 + currentUser[i] - '0';
            ++i;
        }

        if (currentName != this->name || this->hash != currentHash)
        {
            users.push_back(currentUser);
        }
    }
    file.close();

    file.open(constantsInit::FILE_NAME, std::ios::out);
    if (file.fail())
    {
        std::cout << "\033[31mError:\033[0m: Cannot open file " << constantsInit::FILE_NAME << " ! Task terminated" << std::endl;
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

void User::setHash(const size_t &hash)
{
    this->hash = hash;
}