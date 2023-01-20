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
 * <Defining User struct and the corresponding methods.>
 *
 */

#ifndef USER_INFO
#define USER_INFO

#include <string>
#include <cstddef>

struct User
{
public:
    std::string name;
    long balance;

    User(void);
    User(const std::string &, const long &, const size_t &);
    bool UpdateBalance(const long &, const char &);
    bool cancelAccount(const std::string &, const std::size_t &);

private:
    size_t hash;

    void setHash(const size_t &);
    bool saveChanges(void);
};

#endif