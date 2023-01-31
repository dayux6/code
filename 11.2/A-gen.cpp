#include <bits/stdc++.h>

int main()
{
    std::srand(std::time(nullptr));
    std::freopen("range.in", "w", stdout);

    int n = 100000, m = 100000;
    std::cout << n << ' ' << m << std::endl;

    for (int i = 0; i < n; ++i)
        std::cout << rand() % (int)2e4 + 1 << ' ';
    std::cout << std::endl;
    for (int i = 0; i < m; ++i)
    {
        int r = rand() % n + 1;
        std::cout << rand() % r + 1 << ' ' << r << std::endl;
    }
    return 0;
}