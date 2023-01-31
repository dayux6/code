#include <bits/stdc++.h>

int main()
{
    std::freopen("B.in", "r", stdin);

    long long l, r;
    std::cin >> l >> r;

    std::cout << "YES" << std::endl;
    for (long long i = l; i <= r; i += 2)
        std::cout << i << ' ' << i + 1 << std::endl;
    return 0;
}