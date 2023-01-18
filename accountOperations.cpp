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
    std::cout << "\033[31mC\033[0m --> Cancel account" << std::endl;
    std::cout << "\033[36mD\033[0m --> Deposit" << std::endl;
    std::cout << "\033[36mL\033[0m --> Logout" << std::endl;
    std::cout << "\033[36mT\033[0m --> Transfer" << std::endl;
    std::cout << "\033[36mW\033[0m --> Withdraw" << std::endl;
    return;
}

static void cancelAccount(User &user)
{
    if (!user.cancelAccount())
    {
        std::cout << "Error: Cannot close account!. Try again later or contact support." << std::endl;
    }
    std::cout << "Press any key to close...";
    std::getchar();
    return;
}

static void transfer(User &user)
{
    std::string receiverName;
    long double amount = 0;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter the name of the receiver: ";
    std::getline(std::cin, receiverName);

    std::cout << "Enter transfer amount: ";
    std::cin >> amount;

    if (std::cin.fail() || amount < 0 || !isNameValid(receiverName))
    {
        std::cout << "\033[31mError:\033[0m: Invalid input data! Task terminated" << std::endl;
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

    User receiver = getUserInfo(file, receiverName);

    if (receiver.name.empty())
    {
        std::cout << "\033[31mError:\033[0m: User not found." << std::endl;
        return;
    }

    if (!user.UpdateBalance((int)(amount * constantsAccount::ROUND_PRECISION), constantsAccount::WITHDRAW))
    {
        std::cout << "\033[31mError:\033[0m Insufficient balance! Task terminated" << std::endl;
        return;
    }
    if (!receiver.UpdateBalance((int)(amount * constantsAccount::ROUND_PRECISION), constantsAccount::DEPOSIT))
    {
        std::cout << "Error: Cannot transfer balance to " << receiverName << "!" << std::endl;
        std::cout << "Restoring balance..." << std::endl;
        if (!user.UpdateBalance((int)(amount * constantsAccount::ROUND_PRECISION), constantsAccount::DEPOSIT))
        {
            std::cout << "FATAL Error! Cannot restore balance. Account problem found. Contact customer support!" << std::endl;
            std::cout << "Press any key to close...";
            std::getchar();
            exit(EXIT_FAILURE);
        }
        std::cout << "Done" << std::endl;
        return;
    }

    std::cout << "Successful transfer" << std::endl;
};

static void balanceOperation(User &user, const char &TYPE)
{
    long double amount = 0;
    std::cout << "Enter deposit amount: ";
    std::cin >> amount;

    if (std::cin.fail() || amount < 0)
    {
        std::cout << "\033[31mError:\033[0m: Invalid input data! Task terminated" << std::endl;
        return;
    }
    user.UpdateBalance(amount * constantsAccount::ROUND_PRECISION, TYPE);
}

void account(User &user)
{
    std::cout << "\nWelcome back, " << user.name << std::endl;

    while (true)
    {
        std::cout << "You have \033[32;1m ";
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
            cancelAccount(user);
            break;
        case constantsAccount::DEPOSIT:
            std::cout << "Deposit selected" << std::endl;
            balanceOperation(user, constantsAccount::DEPOSIT);
            continue;
        case constantsAccount::LOGOUT:
            std::cout << "Logout selected" << std::endl;
            break;
        case constantsAccount::TRANSFER:
            std::cout << "Transfer selected" << std::endl;
            transfer(user);
            continue;
        case constantsAccount::WITHDRAW:
            std::cout << "Withdraw selected" << std::endl;
            balanceOperation(user, constantsAccount::WITHDRAW);
            continue;

        default:
            std::cout << "Invalid Input." << std::endl;
            continue;
        }
        break;
    }
}