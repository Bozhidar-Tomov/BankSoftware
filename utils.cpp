std::string intToString(int balance)
{
    std::string res;
    bool isNegative = false;

    if (balance < 0)
    {
        isNegative = true;
        res += '-';
        balance *= -1;
    }

    if (balance == 0)
    {
        return "0";
    }

    while (balance)
    {
        res += balance % 10 + '0';
        balance /= 10;
    }
    int size = res.size();

    for (int i = isNegative; i < size / 2; ++i)
    {
        char temp = res[i];
        res[i] = res[size - i - 1 + isNegative];
        res[size - i - 1 + isNegative] = temp;
    }
    return res;
}

int absUtil(const int &num)
{
    return num < 0 ? num * -1 : num;
}