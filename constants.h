#ifndef CONSTANTS
#define CONSTANTS

namespace constantsInit
{
    constexpr char Login{'L'};
    constexpr char Register{'R'};
    constexpr char Quit{'Q'};
    constexpr char Yes{'y'};
    constexpr char allowedSpecialCharacters[8] = {'!', '@', '#', '$', '%', '^', '&', '*'};
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
    constexpr char Cancel{'C'};
    constexpr char Deposit{'D'};
    constexpr char Logout{'L'};
    constexpr char Transfer{'T'};
    constexpr char Withdraw{'W'};
    constexpr double ROUND_PRECISION{100.0};
}

#endif