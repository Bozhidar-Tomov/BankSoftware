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
 * <Declaration of helper functions.>
 *
 */

#ifndef UTILS
#define UTILS

#include <iostream>
#include <cstddef>

struct User;

std::string intToString(int);
int absUtil(const int &);
User getUserInfo(std::fstream &, const std::string &, const std::size_t & = -1);
bool doesUserExists(std::fstream &, const std::string &, const std::size_t & = -1);
bool takeUserInput(std::string &, std::string &);
bool isNameValid(const std::string &);
bool isPasswordValid(const std::string &);
bool isInputValid(const std::string &, const std::string &);
long double castToDouble(const std::string &, const int &);
bool isValidDouble(const std::string &, const int &);

#endif