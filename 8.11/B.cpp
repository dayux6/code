#include <bits/stdc++.h>

const int maxn = 1e3;

int fac[maxn + 1], inv[maxn + 1], f[maxn + 1][maxn + 1], l[maxn + 1][maxn + 1], r[maxn + 1][maxn + 1], lr[maxn + 1][maxn + 1];

int qpow(int x, int n, const int mod)
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

int getinv(int x, const int mod) { return qpow(x, mod - 2, mod); }

int main()
{
    freopen("B.in", "r", stdin);
    int n, k, mod;
    std::cin >> n >> k >> mod;

    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = 1ll * fac[i - 1] * i % mod;
    inv[n] = getinv(fac[n], mod);
    for (int i = n; i >= 1; --i)
        inv[i - 1] = 1ll * inv[i] * i % mod;
    auto C = [=](int n, int m)
    { return 1ll * fac[n] * inv[n - m] % mod * inv[m] % mod; };

    for (int i = 0; i <= k; ++i)
        f[0][i] = l[0][i] = r[0][i] = lr[0][i] = 1;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= k; ++j)
            for (int llen = 0; llen < i; ++llen)
            {
                int rlen = i - llen - 1;
                f[i][j] = (f[i][j] + 1ll * r[llen][j] * l[rlen][j] % mod * C(i - 1, llen) % mod) % mod;
                l[i][j] = (l[i][j] + 1ll * lr[llen][j - 1] * l[rlen][j] % mod * C(i - 1, llen) % mod) % mod;
                r[i][j] = (r[i][j] + 1ll * r[llen][j] * lr[rlen][j - 1] % mod * C(i - 1, llen) % mod) % mod;
                lr[i][j] = (lr[i][j] + ((1ll * lr[llen][j] * lr[rlen][j] % mod - 1ll * ((lr[llen][j] - lr[llen][j - 1]) % mod) * ((lr[rlen][j] - lr[rlen][j - 1]) % mod) % mod) % mod) * C(i - 1, llen) % mod) % mod;
            }

    std::cout << ((f[n][k] - f[n][k - 1]) % mod + mod) % mod << std::endl;
    return 0;
}