#include <bits/stdc++.h>

const int maxn = 500, mod = 998244353;

int c[maxn + 1][maxn + 1], f[maxn + 1][maxn + 2], g[maxn + 1][maxn + 2];

int qpow(int x, int n = mod - 2)
{
    int ret = 1;

    while (n)
    {
        if (n & 1)
            ret = 1ll * ret * x % mod;
        x = 1ll * x * x % mod;
        n >>= 1;
    }

    return ret;
}

int main()
{
    std::freopen("CF1782F.in", "r", stdin);

    int n, q;
    std::cin >> n >> q;

    for (int i = 0; i <= n; ++i)
    {
        c[i][0] = c[i][i] = 1;

        for (int j = 1; j < i; ++j)
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
    }

    int p = 1ll * q * qpow(1e4) % mod;

    std::fill_n(f[0], n + 1, 1);
    std::fill_n(g[0], n + 1, 1);

    int res = 1;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = n - i; j <= n; ++j)
        {
            for (int k = 0; k < i; ++k)
                f[i][j] = (f[i][j] + 1ll * c[i - 1][k] * g[k][j] % mod * (1ll * p * f[i - k - 1][std::max(0, j - 1)] % mod + 1ll * (1 - p) * f[i - k - 1][j + 1] % mod) % mod) % mod;

            for (int k = 0; k <= i; ++k)
                g[i][j] = (g[i][j] + 1ll * c[i][k] * f[k][j] % mod * f[i - k][j] % mod) % mod;
        }

        std::fill_n(f[i], n - i, f[i][n - i]);
        std::fill_n(g[i], n - i, g[i][n - i]);

        res = 1ll * res * qpow(i * 2 - 1) % mod;
    }

    std::cout << (1ll * res * f[n][n] % mod + mod) % mod << std::endl;
    return 0;
}