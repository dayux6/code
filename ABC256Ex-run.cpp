#include <bits/stdc++.h>

int main()
{
    int cnt = 0;
    while (true)
    {
        system("./ABC256Ex-gen > ABC256Ex.in");
        system("./ABC256Ex > ABC256Ex.out");
        system("./ABC256Ex-bf > ABC256Ex.ans");
        if (system("diff ABC256Ex.out ABC256Ex.ans"))
        {
            std::cout << "Wrong Answer" << std::endl;
            break;
        }
        else
            std::cout << "Accepted #" << ++cnt << std::endl;
    }
    return 0;
}