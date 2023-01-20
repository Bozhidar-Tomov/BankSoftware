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
 * <Defining constants available throughout the lifetime of the program.>
 *
 */

#ifndef CONSTANTS
#define CONSTANTS

#include <cstddef>

namespace constantsInit
{
    static constexpr char LOGIN{'L'};
    static constexpr char REGISTER{'R'};
    static constexpr char QUIT{'Q'};
    static constexpr char YES{'y'};
    static constexpr char ALLOWED_SPECIAL_CHARS[8] = {'!', '@', '#', '$', '%', '^', '&', '*'};
    static constexpr char FILE_NAME[10] = {"users.txt"};
    static constexpr unsigned short MIN_LEN_PASSWORD = 5;
    static constexpr unsigned short MAX_LEN_PASSWORD = 20;
    static constexpr unsigned short MIN_LEN_NAME = 3;
    static constexpr unsigned short MAX_LEN_NAME = 20;
}

namespace constantsAccount
{
    static constexpr char CANCEL{'C'};
    static constexpr char DEPOSIT{'D'};
    static constexpr char LOGOUT{'L'};
    static constexpr char TRANSFER{'T'};
    static constexpr char WITHDRAW{'W'};
    static constexpr double ROUND_PRECISION{100.0};
    static constexpr unsigned int OVERDRAFT_LIMIT{1000000};
    static constexpr size_t MAX_BALANCE{100000000000}; // 1 billion currency units (whole base BGN)
    static constexpr unsigned short MAX_AMOUNT_PER_OPERATION = 5000;
}

#endif