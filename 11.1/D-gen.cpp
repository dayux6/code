#include <bits/stdc++.h>

int main()
{
    srand(time(nullptr));
    int n = rand() % 1000 + 1, m = rand() % 1000 + 1;
    std::cout << n << ' ' << m << std::endl;
    for (int i = 1; i <= n; ++i)
        std::cout << rand() % 20000 + 1 << ' ';
    std::cout << std::endl;

    for (int i = 0; i < m; ++i)
    {
        bool b = rand() & 1;
        int r = rand() % n + 1;
        std::cout << b << ' ' << rand() % r + 1 << ' ' << r;
        if (b)
            std::cout << std::endl;
        else
            std::cout << ' ' << rand() % 20000 + 1 << ' ' << rand() % 20000 + 1 << std::endl;
    }
    return 0;
}