#include <bits/stdc++.h>

int main()
{
    freopen("A.in", "r", stdin);
    long long n;
    int m;
    std::cin >> n >> m;
    std::cout << std::fixed << std::setprecision(3) << std::round(std::pow(n, 1.0 / m) * 1e3) / 1e3 << std::endl;
    return 0;
}