#include <bits/stdc++.h>

int main()
{
    int cnt = 0;
    while (true)
    {
        system("./C-gen");
        system("./C > C.out");
        system("./C-bf > C.ans");
        if (system("diff C.out C.ans"))
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