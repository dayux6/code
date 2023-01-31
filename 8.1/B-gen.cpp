#include <bits/stdc++.h>

int main()
{
    srand(time(0));
    int n = 15;
    std::cout << n << std::endl;
    for (int i = 0; i < n; ++i)
        std::cout << (rand() & 1) << ' ';
    std::cout << std::endl;
    for (int i = 1; i < n; ++i)
        std::cout << rand() % i + 1 << ' ';
    std::cout << std::endl;
    return 0;
}