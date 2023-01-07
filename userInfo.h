#ifndef USER_INFO
#define USER_INFO

struct User
{
public:
    std::string name;
    int balance;

    User(void);
    User(const std::string &name, const int &balance, const size_t &hash);
    bool UpdateBalance(const int &balance, const char &type);
    bool cancelAccount(void);

private:
    void setHash(const size_t &hash);
    bool saveChanges(void);
    size_t hash;
};

#endif