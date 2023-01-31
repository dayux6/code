#include <bits/stdc++.h>

const int p = 1e9 + 7, inv2 = (p + 1) / 2;

int qpow(int x, long long n, const int mod)
{
    int ret = 1;
    while (n != 0)
    {
        if (n & 1)
            ret = 1ll * ret * x % mod;
        x = 1ll * x * x % mod;
        n >>= 1;
    }
    return ret;
}

int getinv(int x) { return qpow(x, p - 2, p); }

int main()
{
    freopen("B.in", "r", stdin);
    int t;
    std::cin >> t;
    for (int _ = 0; _ < t; ++_)
    {
        int x;
        long long n;
        std::cin >> x >> n;

        int tmp = qpow(2, n - 1, p - 1), a = qpow(x + 1, tmp, p), b = qpow(x - 1, tmp, p), an = 1ll * (a + b) * inv2 % p, bn = 1ll * (a - b) * inv2 % p;
        std::cout << (1ll * an * getinv(bn) % p + p) % p << std::endl;
    }
    return 0;
}