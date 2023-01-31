#include <bits/stdc++.h>

int main()
{
    srand(time(nullptr));
    std::freopen("car.in", "w", stdout);

    int n = 1e4, m = 1e4;
    std::cout << n << ' ' << m << std::endl;

    for (int i = 0; i < n; ++i)
        std::cout << rand() % 10000 + 1 << ' ' << rand() % 10000 + 1 << std::endl;

    for (int i = 0; i < m; ++i)
    {
        int r = rand() % n + 1;
        std::cout << ((rand() & 1) ? "Add " : "Set ") << rand() % r + 1 << ' ' << r << ' ' << rand() % 10000 + 1 << std::endl;
    }
    return 0;
}