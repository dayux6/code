#include <bits/stdc++.h>

const int mod = 998244353;

int main()
{
    freopen("C.in", "r", stdin);
    int n, k;
    std::cin >> n >> k;
    int ***f = new int **[n + 1];
    for (int i = 1; i <= n; ++i)
    {
        f[i] = new int *[n + 1];
        for (int j = 0; j <= n; ++j)
            f[i][j] = new int[k]();
    }
    f[1][0][1] = n;
    f[1][1][0] = n * (n - 1);
    for (int i = 2; i <= n; ++i)
        for (int j = 0; j <= n; ++j)
            for (int l = 0; l < k; ++l)
            {
                if (l >= i)
                    f[i][j][l] = std::max(0ll, 1ll * f[i - 1][j][l - i] * (j * 2 + 1) % mod * (n - i - j + 1) % mod);
                if (j > 0)
                    f[i][j][l] = (f[i][j][l] + std::max(0ll, 1ll * f[i - 1][j - 1][l] * (n - i - j + 2) % mod * (n - i - j + 1) % mod)) % mod;
                if (j < n && l >= 2 * i)
                    f[i][j][l] = (f[i][j][l] + 1ll * f[i - 1][j + 1][l - 2 * i] * (j + 1) % mod * (j + 1) % mod) % mod;
            }
    int sum = 0;
    for (int i = 0; i < k; ++i)
        sum = (sum + f[n][0][i]) % mod;
    int fac = 1;
    for (int i = 2; i <= n; ++i)
        fac = 1ll * fac * i % mod;
    std::cout << ((1ll * fac * fac % mod - sum) % mod + mod) % mod << std::endl;
    return 0;
}