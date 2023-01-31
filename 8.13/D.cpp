#include <bits/stdc++.h>

typedef long double db;

const int maxn = 1e5;

db res, alpha[maxn + 1];
std::vector<int> g[maxn + 1];

int dfs(int x, int fa)
{
    int siz = 1, max = 0, cnt = 0;
    for (int v : g[x])
        if (v ^ fa)
        {
            ++cnt;
            int tmp = dfs(v, x);
            siz += tmp;
            max = std::max(max, tmp);
        }

    if (cnt != 1)
        for (int v : g[x])
            if (v ^ fa)
                res = std::max(res, (db)max / siz);
    return siz;
}

int main()
{
    freopen("D.in", "r", stdin);
    int n;
    bool k;
    std::cin >> n >> k;

    for (int i = 1; i < n; ++i)
    {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 1; i <= n; ++i)
    {
        res = 0;
        dfs(i, 0);
        alpha[i] = res;
    }

    std::sort(alpha + 1, alpha + n + 1);
    int m, ans = 0;
    std::cin >> m;
    for (int i = 0; i < m; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        a ^= ans * k;
        b ^= ans * k;
        ans = std::upper_bound(alpha + 1, alpha + n + 1, (db)a / b) - alpha - 1;
        std::cout << ans << std::endl;
    }
    return 0;
}