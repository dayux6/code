#include <bits/stdc++.h>

const int mod = 998244353;

int main()
{
    freopen("D.in", "r", stdin);
    int n, k;
    std::cin >> n >> k;
    int **f = new int *[n + 1];
    for (int i = 1; i <= n; ++i)
        f[i] = new int[k + 1]();
    f[1][0] = 1;
    for (int i = 2; i <= n; ++i)
        for (int j = 0; j <= k; ++j)
        {
            f[i][j] = 2ll * (j + 1) % mod * f[i - 1][j] % mod;
            if (j > 0)
                f[i][j] = (f[i][j] + 1ll * std::max(0, i - 2 * j) * f[i - 1][j - 1] % mod) % mod;
        }
    std::cout << f[n][k] << std::endl;
    return 0;
}