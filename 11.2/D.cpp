#include <bits/stdc++.h>

const int maxn = 1e5, maxlg = 16;

int n, fa[maxn + 1], id[maxn + 1], bel[maxn + 1], dep[maxn + 1], sum[maxn + 1][maxlg + 1], dif[maxn + 1][maxlg + 1];
bool mark[maxn + 1];
std::vector<int> g[maxn + 1];

int bfs(int s)
{
    fa[s] = 0;
    std::fill_n(dep + 1, n, 0);
    dep[s] = 1;
    std::queue<int> q({s});

    while (!q.empty())
    {
        int x = q.front();
        q.pop();

        for (int v : g[x])
            if (dep[v] == 0)
            {
                fa[v] = x;
                dep[v] = dep[x] + 1;
                q.emplace(v);
            }
    }

    int ret = 1;
    for (int i = 2; i <= n; ++i)
        if (dep[i] > dep[ret])
            ret = i;
    return ret;
}

int dfs(int x, int fa)
{
    int ret = 0;
    for (int v : g[x])
        if (!mark[v] && v != fa)
        {
            dep[v] = dep[x] + 1;
            bel[v] = bel[x];
            ret = std::max(ret, dfs(v, x) + 1);
        }
    return ret;
}

int querysum(int l, int r)
{
    int k = std::log2(r - l + 1);
    return std::max(sum[l][k], sum[r - (1 << k) + 1][k]);
}

int querydif(int l, int r)
{
    int k = std::log2(r - l + 1);
    return std::max(dif[l][k], dif[r - (1 << k) + 1][k]);
}

int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);

    std::cin >> n;

    for (int i = 1; i < n; ++i)
    {
        int u, v;
        std::cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }

    int s = bfs(1), t = bfs(s), len = dep[t], cur = t;
    while (cur != 0)
    {
        id[dep[cur]] = cur;
        bel[cur] = dep[cur];
        mark[cur] = true;
        cur = fa[cur];
    }

    for (int i = 1; i <= len; ++i)
    {
        dep[id[i]] = 0;
        int tmp = dfs(id[i], 0);
        sum[i][0] = tmp + i;
        dif[i][0] = tmp - i;
    }

    for (int i = 1; i <= maxlg; ++i)
        for (int j = 1; j + (1 << i) - 1 <= len; ++j)
        {
            sum[j][i] = std::max(sum[j][i - 1], sum[j + (1 << (i - 1))][i - 1]);
            dif[j][i] = std::max(dif[j][i - 1], dif[j + (1 << (i - 1))][i - 1]);
        }

    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i)
    {
        int x, y;
        std::cin >> x >> y;

        int u = bel[x], v = bel[y];
        if (u > v)
        {
            std::swap(x, y);
            std::swap(u, v);
        }
        int mid = (u + v + dep[y] - dep[x]) / 2, res = std::max(std::min(dep[x] + u - 1, dep[y] + v - 1), std::min(dep[x] + len - u, dep[y] + len - v));
        if (mid < u)
            mid = u;
        if (mid > v)
            mid = v;
        if (u < mid)
            res = std::max(res, querysum(u + 1, mid) - u + dep[x]);
        if (v > mid + 1)
            res = std::max(res, querydif(mid + 1, v - 1) + v + dep[y]);
        std::cout << res << std::endl;
    }
    return 0;
}