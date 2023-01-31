#include <bits/stdc++.h>

int main()
{
    int cnt = 0;
    while (true)
    {
        system("./B-gen");
        system("./B > B.out");
        system("./B-bf > B.ans");
        if (system("diff B.out B.ans"))
        {
            std::cout << "Wrong Answer" << std::endl;
            break;
        }
        else
        {
            ++cnt;
            std::cout << "Accepted #" << cnt << std::endl;
        }
    }
    return 0;
}