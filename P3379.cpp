#include <bits/stdc++.h>

const int maxn = 5e5, maxlg = 18;

int fa[maxn + 1], dep[maxn + 1], dfc, dfn[maxn + 1], siz[maxn + 1], min[maxn + 1][maxlg + 1];
std::vector<int> t[maxn + 1];

void dfs(int x)
{
    ++dfc;
    dfn[x] = dfc;
    min[dfc][0] = x;
    siz[x] = 1;

    for (int v : t[x])
        if (v != fa[x])
        {
            fa[v] = x;
            dep[v] = dep[x] + 1;
            dfs(v);
            siz[x] += siz[v];
        }
}

int main()
{
#ifndef ONLINE_JUDGE
    std::freopen("P3379.in", "r", stdin);
#endif

    int n, m, rt;
    std::cin >> n >> m >> rt;

    for (int i = 1, u, v; i < n; ++i)
    {
        std::cin >> u >> v;
        t[u].emplace_back(v);
        t[v].emplace_back(u);
    }

    dfs(rt);

    for (int i = 1; i <= maxlg; ++i)
        for (int j = 1; j + (1 << i) - 1 <= n; ++j)
            if (dep[min[j][i - 1]] < dep[min[j + (1 << (i - 1))][i - 1]])
                min[j][i] = min[j][i - 1];
            else
                min[j][i] = min[j + (1 << (i - 1))][i - 1];

    auto query = [&](int l, int r)
    {
        int k = std::log2(r - l + 1);
        if (dep[min[l][k]] < dep[min[r - (1 << k) + 1][k]])
            return min[l][k];
        else
            return min[r - (1 << k) + 1][k];
    };

    for (int i = 0, u, v; i < m; ++i)
    {
        std::cin >> u >> v;

        if (u == v)
        {
            std::cout << u << '\n';
            continue;
        }

        if (dfn[u] > dfn[v])
            std::swap(u, v);
        std::cout << fa[query(dfn[u] + 1, dfn[v])] << '\n';
    }
    return 0;
}