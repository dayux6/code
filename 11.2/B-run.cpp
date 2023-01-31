#include <bits/stdc++.h>

int main()
{
    int cnt = 0;
    while (true)
    {
        std::system("./B-gen");
        std::system("./B-bf");

        long double bg = std::clock();
        std::system("./B");
        long double ed = std::clock();

        if (std::system("diff car.out car.ans"))
        {
            std::cout << "WA" << std::endl;
            break;
        }
        else
            std::cout << "AC #" << ++cnt << ' ' << std::fixed << (ed - bg) / CLOCKS_PER_SEC << std::endl;
    }
    return 0;
}