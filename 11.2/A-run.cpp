#include <bits/stdc++.h>

int main()
{
    int cnt = 0;
    while (true)
    {
        std::system("./A-gen");
        std::system("./A");

        long double bg = std::clock();
        std::system("./A-std");
        long double ed = std::clock();

        if (std::system("diff range.out range.ans"))
        {
            std::cout << "WA" << std::endl;
            break;
        }
        else
            std::cout << "AC #" << ++cnt << ' ' << std::fixed << (ed - bg) / CLOCKS_PER_SEC << std::endl;
    }
    return 0;
}