#include <bits/stdc++.h>

int main()
{
    std::srand(time(nullptr));
    std::freopen("xor.in", "w", stdout);

    int n = 100000;
    std::cout << n << std::endl;

    for (int i = 1; i <= n; ++i)
        std::cout << rand() << ' ';
    std::cout << std::endl;
    return 0;
}