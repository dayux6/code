#include <bits/stdc++.h>

int main()
{
    int cnt = 0;
    while (true)
    {
        system("./C-gen");
        system("./C-bf > C.ans");
        system("./C > C.out");
        if (system("diff C.ans C.out"))
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