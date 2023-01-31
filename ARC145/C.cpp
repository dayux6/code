#include <bits/stdc++.h>

const int maxn = 2e5, mod = 998244353;

int fac[maxn * 2 + 1], inv[maxn * 2 + 1];

int qpow(int x, int n)
{
    int ret = 1;
    while (n)
    {
        if (n & 1)
            ret = 1ll * ret * x % mod;
        x = 1ll * x * x % mod;
        n /= 2;
    }
    return ret;
}

void init()
{
    fac[0] = 1;
    for (int i = 1; i <= maxn * 2; ++i)
        fac[i] = 1ll * fac[i - 1] * i % mod;
    inv[maxn * 2] = qpow(fac[maxn * 2], mod - 2);
    for (int i = maxn * 2; i; --i)
        inv[i - 1] = 1ll * inv[i] * i % mod;
}

int C(int n, int m) { return 1ll * fac[n] * inv[n - m] % mod * inv[m] % mod; }

int main()
{
    freopen("C.in", "r", stdin);
    init();
    int n;
    std::cin >> n;
    std::cout << 1ll * qpow(2, n) * fac[n] % mod * C(n * 2, n) % mod * qpow(n + 1, mod - 2) % mod << std::endl;
    return 0;
}