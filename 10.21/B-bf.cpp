#include <bits/stdc++.h>

const int maxn = 1e5, mod = 1e9 + 7;

int f[maxn + 1], s[maxn + 1], ans[maxn];
std::vector<int> g[maxn + 1];
std::vector<std::pair<int, int>> q[maxn + 1];

void dp(int x, int fa)
{
    f[x] = g[x].size();

    for (int v : g[x])
        if (v != fa)
        {
            dp(v, x);
            f[x] = (f[x] + f[v]) % mod;
        }
}

void stat(int x, int fa)
{
    for (int v : g[x])
        if (v != fa)
        {
            s[v] = (s[x] + f[v]) % mod;
            stat(v, x);
        }
}

int main()
{
    std::freopen("tree.in", "r", stdin);
    std::freopen("tree.out", "w", stdout);

    int n, m;
    std::cin >> n >> m;

    for (int i = 1; i < n; ++i)
    {
        int u, v;
        std::cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }

    for (int i = 0; i < m; ++i)
    {
        int s, t;
        std::cin >> s >> t;
        q[t].emplace_back(s, i);
    }

    for (int i = 1; i <= n; ++i)
        if (!q[i].empty())
        {
            dp(i, i);
            s[i] = 0;
            stat(i, i);

            for (std::pair<int, int> pr : q[i])
                ans[pr.second] = s[pr.first];
        }

    for (int i = 0; i < m; ++i)
        std::cout << ans[i] << std::endl;
    return 0;
}