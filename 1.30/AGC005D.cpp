#include <bits/stdc++.h>

const int maxn = 2e3, mod = 924844033;

int fac[maxn + 1], f[maxn * 2 + 1][maxn + 1][2];
bool flg[maxn * 2 + 1];

int main()
{
    std::freopen("AGC005D.in", "r", stdin);

    int n, k;
    std::cin >> n >> k;

    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = 1ll * fac[i - 1] * i % mod;

    int tot = 0;
    for (int i = 1; i <= k; ++i)
        for (int j = 0; j < 2; ++j)
            for (int l = i; l <= n; l += k)
            {
                ++tot;
                flg[tot] = i != l;
            }

    f[0][0][0] = 1;
    for (int i = 1; i <= tot; ++i)
        for (int j = 0; j <= n; ++j)
        {
            f[i][j][0] = (f[i - 1][j][0] + f[i - 1][j][1]) % mod;
            if (j != 0 && flg[i])
                f[i][j][1] = f[i - 1][j - 1][0];
        }

    int ans = 0;
    for (int i = 0; i <= n; ++i)
        ans = (ans + (i & 1 ? -1ll : 1ll) * fac[n - i] * (f[tot][i][0] + f[tot][i][1]) % mod) % mod;

    std::cout << (ans + mod) % mod << std::endl;
    return 0;
}