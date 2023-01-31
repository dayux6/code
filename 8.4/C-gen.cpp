#include <bits/stdc++.h>

int main()
{
    freopen("C.in", "w", stdout);
    srand(time(nullptr));
    int n = 6;
    std::cout << n << std::endl;
    int *p = new int[n + 1];
    std::iota(p + 1, p + n + 1, 1);
    std::random_shuffle(p + 1, p + n + 1);
    for (int i = 1; i <= n; ++i)
        std::cout << p[i] << ' ';
    std::cout << std::endl;
    for (int i = 1; i <= n; ++i)
        std::cout << rand() % 10 + 1 << ' ';
    std::cout << std::endl;
    return 0;
}