#include <bits/stdc++.h>

const int mod = 998244353;

int main()
{
    freopen("D.in", "r", stdin);
    int n, k;
    std::cin >> n >> k;
    int ***f = new int **[n + 1];
    for (int i = 0; i <= n; ++i)
    {
        f[i] = new int *[n + 1];
        for (int j = 1; j <= n; ++j)
            f[i][j] = new int[k + 1]();
    }
    f[1][1][0] = 1;
    for (int i = 2; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            for (int l = 0; l <= k; ++l)
            {
                if (l >= i)
                    f[i][j][l] = (f[i][j][l] + 2ll * f[i - 1][j][l - i] % mod) % mod;
                if (j > 1)
                    f[i][j][l] = (f[i][j][l] + f[i - 1][j - 1][l]) % mod;
                if (j < n && l >= i * 2)
                    f[i][j][l] = (f[i][j][l] + f[i - 1][j + 1][l - i * 2]) % mod;
                f[i][j][l] = 1ll * j * f[i][j][l] % mod;
            }
    int sum = 0;
    for (int i = 0; i <= k; ++i)
        sum = (sum + f[n][1][i]) % mod;
    std::cout << sum << std::endl;
    return 0;
}