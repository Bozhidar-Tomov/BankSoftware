/**
 *
 * Solution to course project # 9
 * Introduction to programming course
 * Faculty of Mathematics and Informatics of Sofia University
 * Winter semester 2022/2023
 *
 * @author Bozhidar Tomov
 * @idnumber 0MI0600171
 * @compiler GCC
 *
 * <Implementing core functionalities.>
 *
 */

#include "accountOperations.h"

#include "userInfo.h"
#include "constants.h"
#include "utils.h"

#include <iostream>
#include <limits>
#include <fstream>
#include <iomanip>

static void displayAccountOptions(void)
{
    std::cout << "\033[4m Choose an option: \033[0m" << std::endl;
    std::cout << "\033[31;1mC\033[0m --> Cancel account" << std::endl;
    std::cout << "\033[36mD\033[0m --> Deposit" << std::endl;
    std::cout << "\033[36mL\033[0m --> Logout" << std::endl;
    std::cout << "\033[36mT\033[0m --> Transfer" << std::endl;
    std::cout << "\033[36mW\033[0m --> Withdraw" << std::endl;
    return;
}

static bool cancelAccount(User &user)
{
    std::string name;
    std::string password;

    if (!takeUserInput(name, password))
    {
        return false;
    }

    size_t hash = std::hash<std::string>{}(password);

    if (!user.cancelAccount(name, hash))
    {
        std::cout << "\033[31mError:\033[0m Cannot close account!. "
                  << "Try again later or contact support." << std::endl;
        return false;
    }
    return true;
}

static void transfer(User &user)
{
    std::string receiverName;
    long double amount = 0;
    std::string amountStr;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter the name of the receiver: ";
    std::getline(std::cin, receiverName);

    std::cout << "Enter transfer amount: ";
    std::getline(std::cin, amountStr);

    if (!isValidDouble(amountStr, amountStr.size()))
    {
        std::cout << "\033[31mError:\033[0m Invalid input data! Task terminated" << std::endl;
        return;
    }

    amount = castToDouble(amountStr, amountStr.size());

    if (std::cin.fail() || !isNameValid(receiverName))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\033[31mError:\033[0m Invalid input data! Task terminated" << std::endl;
        return;
    }

    if (amount <= 0 || amount > constantsAccount::MAX_AMOUNT_PER_OPERATION)
    {
        std::cout << "\033[31mError:\033[0m Amount per operation should be in the range [0.01 - 5000.00]. "
                  << "Task terminated." << std::endl;
        return;
    }

    std::fstream file;
    file.open(constantsInit::FILE_NAME, std::ios::in);
    if (!file.is_open())
    {
        std::cout << "\033[31mError:\033[0m " << constantsInit::FILE_NAME << " file does not exist." << std::endl;

        std::cout << "Press any key to close...";
        std::getchar();
        exit(EXIT_FAILURE);
    }

    if (receiverName == user.name)
    {
        std::cout << "Invalid Receiver! Task terminated." << std::endl;
        return;
    }

    User receiver = getUserInfo(file, receiverName);

    if (receiver.name.empty())
    {
        std::cout << "\033[31mError:\033[0m Receiver not found." << std::endl;
        return;
    }

    if (!user.UpdateBalance((long)(amount * constantsAccount::ROUND_PRECISION), constantsAccount::WITHDRAW))
    {
        std::cout << "\033[31mError:\033[0m Insufficient balance! Task terminated" << std::endl;
        return;
    }

    if (!receiver.UpdateBalance((long)(amount * constantsAccount::ROUND_PRECISION), constantsAccount::DEPOSIT))
    {
        std::cout << "\033[31mError:\033[0m Cannot transfer balance to " << receiverName << "!" << std::endl;
        std::cout << "Restoring balance..." << std::endl;

        if (!user.UpdateBalance((long)(amount * constantsAccount::ROUND_PRECISION), constantsAccount::DEPOSIT))
        {
            std::cout << "\033[41m\033[37;1mFATAL Error!\033[0m Cannot restore balance. "
                      << "Account problem found. Contact customer support!" << std::endl;
            std::cout << "Press any key to close...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getchar();
            exit(EXIT_FAILURE);
        }
        std::cout << "Done" << std::endl;
        return;
    }

    std::cout << "Successful transfer." << std::endl;
};

static void balanceOperation(User &user, const char &TYPE)
{
    long double amount = 0;
    std::string amountStr;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter deposit amount: ";
    std::getline(std::cin, amountStr);

    if (!isValidDouble(amountStr, amountStr.size()))
    {
        std::cout << "\033[31mError:\033[0m Invalid input data! Task terminated" << std::endl;
        return;
    }

    amount = castToDouble(amountStr, amountStr.size());

    if (amount <= 0 || amount > constantsAccount::MAX_AMOUNT_PER_OPERATION)
    {
        std::cout << "\033[31mError:\033[0m Amount per operation should be in the range [0.01 - 5000.00]. "
                  << "Task terminated." << std::endl;
        return;
    }

    user.UpdateBalance((long)(amount * constantsAccount::ROUND_PRECISION), TYPE);
}

void account(User &user)
{
    std::cout << "\nWelcome back, " << user.name << std::endl;

    while (true)
    {
        std::cout << "\nBalance \033[32;1m ";
        std::cout << std::fixed << std::setprecision(2) << user.balance / constantsAccount::ROUND_PRECISION;
        std::cout << " BGN\033[0m\n";
        std::cout << std::endl;

        displayAccountOptions();

        char input = '\0';
        std::cin >> input;

        switch (input)
        {
        case constantsAccount::CANCEL:
            std::cout << "Cancel selected" << std::endl;
            if (cancelAccount(user))
            {
                return;
            }
            continue;
        case constantsAccount::DEPOSIT:
            std::cout << "Deposit selected" << std::endl;
            balanceOperation(user, constantsAccount::DEPOSIT);
            continue;
        case constantsAccount::LOGOUT:
            std::cout << "Logout selected" << std::endl;
            return;
        case constantsAccount::TRANSFER:
            std::cout << "Transfer selected" << std::endl;
            transfer(user);
            continue;
        case constantsAccount::WITHDRAW:
            std::cout << "Withdraw selected" << std::endl;
            balanceOperation(user, constantsAccount::WITHDRAW);
            continue;
        default:
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid Input." << std::endl;
            continue;
        }
    }
    return;
}