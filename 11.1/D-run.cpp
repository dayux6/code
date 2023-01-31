#include <bits/stdc++.h>

int main()
{
    int cnt = 0;
    while (true)
    {
        std::system("./D-gen > D.in");
        std::system("./D-std > D.ans");
        std::system("./D > D.out");

        if (std::system("diff D.out D.ans"))
        {
            std::cout << "WA" << std::endl;
            break;
        }
        else
            std::cout << "AC #" << ++cnt << std::endl;
    }
    return 0;
}