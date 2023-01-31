#include <bits/stdc++.h>

int main()
{
    int cnt = 0;
    while (true)
    {
        system("./gen");
        system("./std");
        system("./test");
        if (system("diff number.out number.ans"))
        {
            std::cout << "Wrong Answer" << std::endl;
            break;
        }
        else
            std::cout << "Accepted #" << ++cnt << std::endl;
    }
    return 0;
}