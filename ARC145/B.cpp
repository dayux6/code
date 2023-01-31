#include <bits/stdc++.h>

int main()
{
    freopen("B.in", "r", stdin);
    long long n, a, b;
    std::cin >> n >> a >> b;
    if (n < a)
        std::cout << 0 << std::endl;
    else if (a <= b)
        std::cout << n - a + 1 << std::endl;
    else
        std::cout << (n / a - 1) * b + std::min(n % a, b - 1) + 1 << std::endl;
    return 0;
}