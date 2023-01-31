#include <bits/stdc++.h>

int main()
{
    srand(time(nullptr));

    std::freopen("lele.in", "w", stdout);

    int n = 20;
    std::cout << n << std::endl;

    for (int i = 1; i <= n; ++i)
        std::cout << rand() % 100 + 1 << ' ' << rand() % 100 + 1 << std::endl;

    for (int i = 2; i <= n; ++i)
        std::cout << rand() % (i - 1) + 1 << std::endl;
    return 0;
}