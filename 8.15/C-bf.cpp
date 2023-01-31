#include <bits/stdc++.h>

const int maxn = 2e5, maxp = 2e5;

int n, X[maxp];
long long dis[maxn + 1], res[maxp];
bool vis[maxn + 1];

struct edge
{
    int v, w;

    edge(int _v, int _w) : v(_v), w(_w) {}
};
std::vector<edge> g[maxn + 1];

void dijkstra(int s)
{
    std::fill_n(dis + 1, n, LLONG_MAX);
    dis[s] = 0;
    std::fill_n(vis + 1, n, false);
    std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<std::pair<long long, int>>> q;
    q.emplace(dis[s], s);
    while (!q.empty())
    {
        int x = q.top().second;
        q.pop();

        if (!vis[x])
        {
            vis[x] = true;

            for (edge e : g[x])
                if (dis[e.v] > dis[x] + e.w)
                {
                    dis[e.v] = dis[x] + e.w;
                    if (!vis[e.v])
                        q.emplace(dis[e.v], e.v);
                }
        }
    }
}

int main()
{
    freopen("C.in", "r", stdin);
    int m, p;
    std::cin >> n >> m >> p;

    for (int i = 0; i < p; ++i)
        std::cin >> X[i];

    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    std::fill_n(res, p, LLONG_MAX);
    for (int i = 0; i < p; ++i)
    {
        dijkstra(X[i]);
        for (int j = 0; j < p; ++j)
            if (i != j)
            {
                res[i] = std::min(res[i], dis[X[j]]);
                res[j] = std::min(res[j], dis[X[j]]);
            }
    }

    for (int i = 0; i < p; ++i)
        std::cout << res[i] << ' ';
    std::cout << std::endl;
    return 0;
}