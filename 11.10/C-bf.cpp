#include <bits/stdc++.h>

const int maxn = 50, mod = 998244353;

int main()
{
    std::freopen("coin.in", "r", stdin);
    std::freopen("coin.out", "w", stdout);

    int n, m;
    std::cin >> n >> m;

    int f[m + 1];
    f[0] = 1;
    std::fill_n(f + 1, m, 0);
    for (int i = 0; i < n; ++i)
    {
        int v;
        std::cin >> v;

        for (int j = v; j <= m; ++j)
            f[j] = (f[j] + f[j - v]) % mod;
    }

    std::cout << f[m] << std::endl;
    return 0;
}