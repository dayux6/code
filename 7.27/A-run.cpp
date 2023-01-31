#include <bits/stdc++.h>

int main()
{
    int cnt = 0;
    while (true)
    {
        system("./A-gen");
        system("./A > A.out");
        system("./A-bf > A.ans");
        if (system("diff A.out A.ans"))
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