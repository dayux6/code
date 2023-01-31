#include <bits/stdc++.h>

const int maxn = 3e3;

int ind[maxn + 1];
bool b[maxn + 1], vis[maxn + 1];
long long dis[maxn + 1], f[maxn + 1];
std::vector<int> dag[maxn + 1];

struct edge
{
    int v, w;

    edge(int _v, int _w) : v(_v), w(_w) {}
};
std::vector<edge> g[maxn + 1], pre[maxn + 1];

int main()
{
    freopen("B.in", "r", stdin);
    int n, m;
    std::cin >> n >> m;

    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        pre[v].emplace_back(u, w);
    }

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> ind[i];
        for (int j = 1; j <= ind[i]; ++j)
        {
            int x;
            std::cin >> x;
            dag[x].push_back(i);
        }
    }

    std::fill_n(dis + 2, n - 1, INT_MAX / 2);
    dis[1] = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
    q.emplace(dis[1], 1);
    while (!q.empty())
    {
        int x = q.top().second;
        q.pop();

        if (!vis[x])
        {
            vis[x] = true;

            for (int v : dag[x])
            {
                --ind[v];

                if (!ind[v])
                {
                    for (edge e : pre[v])
                        dis[v] = std::min(dis[v], std::max(dis[x], dis[e.v] + e.w));
                    q.emplace(dis[v], v);
                }
            }

            for (edge e : g[x])
                if (!ind[e.v] && dis[e.v] > dis[x] + e.w)
                {
                    dis[e.v] = dis[x] + e.w;
                    if (!vis[e.v])
                        q.emplace(dis[e.v], e.v);
                }
        }
    }

    std::cout << dis[n] << std::endl;
    return 0;
}