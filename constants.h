#ifndef CONSTANTS
#define CONSTANTS

#include <cstddef>

namespace constantsInit
{
    constexpr char LOGIN{'L'};
    constexpr char REGISTER{'R'};
    constexpr char QUIT{'Q'};
    constexpr char YES{'y'};
    constexpr char ALLOWED_SPECIAL_CHARS[8] = {'!', '@', '#', '$', '%', '^', '&', '*'};
    constexpr char FILE_NAME[10] = {
        'u',
        's',
        'e',
        'r',
        's',
        '.',
        't',
        'x',
        't',
        '\0'};
    const unsigned short MIN_LEN_PASSWORD = 5;
    const unsigned short MAX_LEN_PASSWORD = 20;
}

namespace constantsAccount
{
    static constexpr char CANCEL{'C'};
    static constexpr char DEPOSIT{'D'};
    static constexpr char LOGOUT{'L'};
    static constexpr char TRANSFER{'T'};
    static constexpr char WITHDRAW{'W'};
    static constexpr double ROUND_PRECISION{100.0};
    static constexpr int OVERDRAFT_LIMIT{1000000};
    static constexpr size_t MAX_BALANCE{100000000000}; // 1 billion currency units (whole base BGN)
}

#endif