std::string intToString(int balance)
{
    std::string res;

    while (balance)
    {
        res += balance % 10 + '0';
        balance /= 10;
    }
    int size = res.size();

    for (int i = 0; i < size / 2; ++i)
    {
        char temp = res[i];
        res[i] = res[size - i - 1];
        res[size - i - 1] = temp;
    }
    return res;
}