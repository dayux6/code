#include <bits/stdc++.h>

const int maxn = 1e5, mod = 1e9 + 7;

int fac[maxn + 1], inv[maxn + 1];

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

int getinv(int x) { return qpow(x, mod - 2); }

int main()
{
    freopen("B.in", "r", stdin);
    fac[0] = 1;
    for (int i = 1; i <= maxn; ++i)
        fac[i] = 1ll * fac[i - 1] * i % mod;
    inv[maxn] = getinv(fac[maxn]);
    for (int i = maxn; i >= 1; --i)
        inv[i - 1] = 1ll * inv[i] * i % mod;
    auto C = [=](int n, int m)
    { return 1ll * fac[n] * inv[n - m] % mod * inv[m] % mod; };
    int id, q;
    std::cin >> id >> q;
    for (int i = 0; i < q; ++i)
    {
        int n, m;
        std::cin >> n >> m;
        int res = 0;
        for (int j = 0; j <= m; ++j)
            res = (res + C(n, j)) % mod;
        std::cout << res << std::endl;
    }
    return 0;
}