#include <bits/stdc++.h>

const int maxn = 1e5, maxlim = 316, mod = 23333333;

int f[maxlim + 1][maxn + 1], g[maxlim + 1][maxn + 1];

int main()
{
    freopen("D.in", "r", stdin);
    int n;
    std::cin >> n;
    int lim = sqrt(n);
    f[0][0] = 1;
    for (int i = 1; i <= lim; ++i)
    {
        std::copy_n(f[i - 1], i, f[i]);
        for (int j = i; j <= n; ++j)
        {
            f[i][j] = (f[i][j - i] + f[i - 1][j]) % mod;
            if (j >= i * (i + 1))
                f[i][j] = (f[i][j] - f[i - 1][j - i * (i + 1)]) % mod;
        }
    }
    g[0][0] = 1;
    int sum = f[lim][n];
    for (int i = 1; i <= lim; ++i)
        for (int j = i * (lim + 1); j <= n; ++j)
        {
            g[i][j] = (g[i - 1][j - lim - 1] + g[i][j - i]) % mod;
            sum = (sum + 1ll * f[lim][n - j] * g[i][j] % mod) % mod;
        }
    std::cout << (sum + mod) % mod << std::endl;
    return 0;
}