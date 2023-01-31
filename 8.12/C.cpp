#include <bits/stdc++.h>

const int maxn = 1e4;

int dis[maxn + 1];
bool vis[maxn + 1];

struct edge
{
    int v, w;

    edge(int _v, int _w) : v(_v), w(_w) {}
};
std::vector<edge> g[maxn + 1];

int main()
{
    freopen("C.in", "r", stdin);
    int t;
    std::cin >> t;
    for (int _ = 0; _ < t; ++_)
    {
        int n, m;
        std::cin >> n >> m;

        for (int i = 1; i <= n; ++i)
            g[i].clear();
        for (int i = 0; i < m; ++i)
        {
            int u, v, w;
            std::cin >> u >> v >> w;
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }

        int min = INT_MAX;
        auto dijkstra = [&](int k)
        {
            std::fill_n(dis + 2, n - 1, INT_MAX);
            std::fill_n(vis + 2, n - 1, false);

            std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
            for (edge e : g[1])
                if (!((e.v >> k) & 1))
                {
                    dis[e.v] = e.w;
                    q.emplace(dis[e.v], e.v);
                }

            while (!q.empty())
            {
                int x = q.top().second;
                q.pop();

                if (!vis[x])
                {
                    vis[x] = true;
                    for (edge e : g[x])
                        if (e.v != 1 && dis[e.v] > dis[x] + e.w)
                        {
                            dis[e.v] = dis[x] + e.w;
                            if (!vis[e.v])
                                q.emplace(dis[e.v], e.v);
                        }
                }
            }

            for (edge e : g[1])
                if (((e.v >> k) & 1) && dis[e.v] != INT_MAX)
                    min = std::min(min, dis[e.v] + e.w);
        };

        int max = 0;
        for (edge e : g[1])
            max = std::max(max, e.v);

        for (int i = 0; i <= log2(max); ++i)
            dijkstra(i);

        std::cout << (min == INT_MAX ? -1 : min) << std::endl;
    }
    return 0;
}