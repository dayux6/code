#include <bits/stdc++.h>

int main()
{
    freopen("B.in", "w", stdout);
    srand(time(0));
    int q = 1000;
    std::cout << rand() << ' ' << q << std::endl;
    for (int i = 0; i < q; ++i)
    {
        int n = rand() % 100000;
        std::cout << n << ' ' << rand() % (n + 1) << std::endl;
    }
    return 0;
}