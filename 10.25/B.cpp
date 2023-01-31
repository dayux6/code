#include <bits/stdc++.h>

const int maxn = 1e3;

int n, dis[maxn + 1];
bool inq[maxn + 1];

struct edge
{
    int v, l, r;

    edge(int _v, int _l, int _r) : v(_v), l(_l), r(_r) {}
};
std::vector<edge> g[maxn + 1];

int spfa(int lim)
{
    dis[1] = INT_MAX;
    std::fill_n(dis + 2, n - 1, 0);
    inq[1] = true;
    std::queue<int> q({1});

    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        inq[x] = false;

        for (edge e : g[x])
            if (e.l <= lim && std::min(dis[x], e.r) > dis[e.v])
            {
                dis[e.v] = std::min(dis[x], e.r);
                if (!inq[e.v])
                {
                    q.emplace(e.v);
                    inq[e.v] = true;
                }
            }
    }

    return dis[n];
}

int main()
{
    std::freopen("silence.in", "r", stdin);
    std::freopen("silence.out", "w", stdout);

    int m;
    std::cin >> n >> m;

    std::set<int> vl;
    for (int i = 0; i < m; ++i)
    {
        int u, v, l, r;
        std::cin >> u >> v >> l >> r;
        g[u].emplace_back(v, l, r);
        g[v].emplace_back(u, l, r);
        vl.emplace(l);
    }

    int max = 0, ansl;
    for (int l : vl)
    {
        int tmp = spfa(l) - l + 1;
        if (tmp > max)
        {
            max = tmp;
            ansl = l;
        }
    }

    std::printf("%d\n", max);
    for (int i = 0; i < max; ++i)
        printf("%d ", ansl + i);
    return 0;
}