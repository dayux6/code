#include <bits/stdc++.h>

int main()
{
    srand(time(0));
    int n = 20, q = 20;
    std::cout << n << ' ' << q << std::endl;
    for (int i = 0; i < n; ++i)
        std::cout << rand() % 100 + 1 << ' ';
    for (int i = 0; i < q; ++i)
    {
        int op = rand() % 3 + 1;
        std::cout << op << ' ';
        int r = rand() % n + 1;
        std::cout << rand() % r + 1 << ' ' << r;
        if (op <= 2)
            std::cout << ' ' << rand() % 5 + 1;
        std::cout << std::endl;
    }
    return 0;
}