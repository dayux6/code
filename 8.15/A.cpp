#include <bits/stdc++.h>

int inv;

int getinv(int x, const int mod)
{
    if (x == 0 || x == 1)
        return 1;

    return (mod - 1ll * (mod / x) * getinv(mod % x, mod) % mod) % mod;
}

int main()
{
    freopen("A.in", "r", stdin);
    int n, a, b;
    std::cin >> n >> a >> b;
    int g = std::__gcd(a, b);
    a /= g;
    b /= g;

    if (a > b)
        std::swap(a, b);
    inv = getinv(a, b);

    bool flg = true;
    long long sum = 0;
    for (int i = 0; i < n; ++i)
    {
        int x;
        std::cin >> x;
        if (x % g != 0)
        {
            flg = false;
            break;
        }

        int k1 = (b - 1ll * x * inv % b) % b, k2 = (1ll * x * inv % b + b) % b;
        sum += std::min(k1 + std::abs(x + 1ll * k1 * a) / b, k2 + std::abs(x - 1ll * k2 * a) / b);
    }

    if (flg)
        std::cout << sum << std::endl;
    else
        std::cout << -1 << std::endl;
    return 0;
}