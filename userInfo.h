#ifndef USER_INFO
#define USER_INFO

struct User
{
public:
    std::string name;
    double balance;

    User();
    User(const std::string &name, const double &balance);
    void UpdateBalance(const int &balance);

private:
    bool saveChanges(int balance);
};

#endif