#include <bits/stdc++.h>

const int maxn = 5e3, mod = 998244353;

int n, siz[maxn + 1], tmpf[maxn + 1], tmpg[maxn + 1], f[maxn + 1][maxn + 1], g[maxn + 1][maxn + 1];
std::vector<int> t[maxn + 1];

void dfs(int x, int fa)
{
    siz[x] = f[x][0] = g[x][1] = 1;

    for (int v : t[x])
        if (v != fa)
        {
            dfs(v, x);

            std::fill_n(tmpf, siz[x] + siz[v], 0);
            std::fill_n(tmpg, siz[x] + siz[v] + 1, 0);

            for (int i = 0; i <= siz[x]; ++i)
                for (int j = 0; j <= siz[v]; ++j)
                {
                    tmpf[i + j] = (tmpf[i + j] + 1ll * f[x][i] * (f[v][j] + g[v][j]) % mod) % mod;
                    tmpg[i + j] = (tmpg[i + j] + 1ll * g[x][i] * f[v][j] % mod) % mod;

                    if (i + j > 0)
                        tmpg[i + j - 1] = (tmpg[i + j - 1] + 1ll * g[x][i] * g[v][j] % mod) % mod;
                }

            siz[x] += siz[v];

            std::copy_n(tmpf, siz[x], f[x]);
            std::copy_n(tmpg, siz[x] + 1, g[x]);
        }
}

int main()
{
    std::freopen("F.in", "r", stdin);

    std::cin >> n;

    for (int i = 1, u, v; i < n; ++i)
    {
        std::cin >> u >> v;
        t[u].emplace_back(v);
        t[v].emplace_back(u);
    }

    dfs(1, 1);

    for (int i = 1; i <= n; ++i)
        std::cout << (f[1][i] + g[1][i]) % mod << std::endl;
    return 0;
}