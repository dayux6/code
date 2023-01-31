#include <bits/stdc++.h>

const int maxn = 2e5;

int dep[maxn * 2 + 2];

int main()
{
    int n;
    std::cin >> n;

    for (int i = 1; i <= n; ++i)
    {
        int a;
        std::cin >> a;
        dep[i * 2] = dep[i * 2 + 1] = dep[a] + 1;
    }

    for (int i = 1; i <= n * 2 + 1; ++i)
        std::cout << dep[i] << std::endl;
    return 0;
}