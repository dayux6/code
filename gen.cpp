#include <bits/stdc++.h>

int main()
{
    std::freopen("number.in", "w", stdout);
    srand(time(nullptr));

    std::cout << 1 << std::endl
              << 50 << std::endl;
    for (int i = 1; i <= 50; ++i)
        std::cout << rand() % 100 + 1 << ' ';
    std::cout << std::endl;
    for (int i = 1; i <= 50; ++i)
        std::cout << (rand() & 1) << ' ';
    return 0;
}