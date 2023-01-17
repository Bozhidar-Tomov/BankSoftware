#ifndef UTILS
#define UTILS

#include <iostream>

struct User;

std::string intToString(int);
int absUtil(const int &);
User getUserInfo(std::fstream &, const std::string &, const std::size_t & = -1);
bool doesUserExists(std::fstream &, const std::string &, const std::size_t & = -1);
bool takeUserInput(std::string &, std::string &);
bool isNameValid(const std::string &);
bool isPasswordValid(const std::string &);
bool isInputValid(const std::string &, const std::string &);

#endif