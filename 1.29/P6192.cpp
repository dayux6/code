#include <bits/stdc++.h>

const int maxn = 100, maxk = 10;

int n, f[1 << maxk][maxn + 1];
bool vis[maxn + 1];

struct edge
{
    int v, w;

    edge(int _v, int _w)
    {
        v = _v;
        w = _w;
    }
};
std::vector<edge> g[maxn + 1];

void dijkstra(int S)
{
    std::fill_n(vis + 1, n, false);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
    for (int i = 1; i <= n; ++i)
        if (f[S][i] != INT_MAX)
            q.emplace(f[S][i], i);

    while (!q.empty())
    {
        int x = q.top().second;
        q.pop();

        if (!vis[x])
        {
            vis[x] = true;

            for (edge e : g[x])
                if (f[S][e.v] > f[S][x] + e.w)
                {
                    f[S][e.v] = f[S][x] + e.w;
                    q.emplace(f[S][e.v], e.v);
                }
        }
    }
}

int main()
{
    std::freopen("P6192.in", "r", stdin);

    int m, k;
    std::cin >> n >> m >> k;

    for (int i = 0, u, v, w; i < m; ++i)
    {
        std::cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    for (int i = 0; i < (1 << k); ++i)
        std::fill_n(f[i] + 1, n, INT_MAX);
    for (int i = 0, x; i < k; ++i)
    {
        std::cin >> x;
        f[1 << i][x] = 0;
    }

    for (int i = 0; i < (1 << k); ++i)
    {
        for (int S = i & (i - 1); S != 0; S = i & (S - 1))
            for (int x = 1; x <= n; ++x)
                if (f[S][x] != INT_MAX && f[i ^ S][x] != INT_MAX)
                    f[i][x] = std::min(f[i][x], f[S][x] + f[i ^ S][x]);

        dijkstra(i);
    }

    int min = INT_MAX;
    for (int x = 1; x <= n; ++x)
        min = std::min(min, f[(1 << k) - 1][x]);

    std::cout << min << std::endl;
    return 0;
}