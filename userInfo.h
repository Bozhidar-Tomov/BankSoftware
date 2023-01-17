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
    bool cancelAccount(void);

private:
    size_t hash;

    void setHash(const size_t &);
    bool saveChanges(void);
};

#endif