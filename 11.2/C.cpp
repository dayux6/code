#include <bits/stdc++.h>

const int maxn = 1000;

int wt[maxn + 1], val[maxn + 1], ind[maxn + 1], f[maxn + 1][maxn + 1], h[maxn + 1][maxn + 1];

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

int main()
{
    std::freopen("travel.in", "r", stdin);
    std::freopen("travel.out", "w", stdout);

    int n, m, lim;
    std::cin >> n >> m >> lim;

    for (int i = 1; i <= n; ++i)
        std::cin >> wt[i] >> val[i];
    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        ++ind[v];
        g[u].emplace_back(v, w);
    }

    for (int i = 1; i <= n; ++i)
    {
        std::fill_n(f[i], lim + 1, -1);
        std::fill_n(h[i], lim + 1, INT_MAX);
    }

    f[1][0] = h[1][0] = 0;
    std::queue<int> q;
    for (int i = 1; i <= n; ++i)
        if (ind[i] == 0)
            q.emplace(i);
    while (!q.empty())
    {
        int x = q.front();
        q.pop();

        for (int i = lim; i >= wt[x]; --i)
            if (f[x][i - wt[x]] != -1)
            {
                int tmp = f[x][i - wt[x]] + val[x];
                if (f[x][i] < tmp)
                {
                    f[x][i] = tmp;
                    h[x][i] = h[x][i - wt[x]];
                }
                else if (f[x][i] == tmp && h[x][i - wt[x]] < h[x][i])
                    h[x][i] = h[x][i - wt[x]];
            }

        for (edge e : g[x])
        {
            --ind[e.v];
            if (ind[e.v] == 0)
                q.emplace(e.v);
            for (int i = 0; i <= lim; ++i)
                if (f[x][i] != -1)
                {
                    if (f[x][i] > f[e.v][i])
                    {
                        f[e.v][i] = f[x][i];
                        h[e.v][i] = h[x][i] + i * e.w;
                    }
                    else if (f[x][i] == f[e.v][i] && h[x][i] + i * e.w < h[e.v][i])
                        h[e.v][i] = h[x][i] + i * e.w;
                }
        }
    }

    int max = 0, min = INT_MAX;
    for (int i = lim; i >= 0; --i)
        if (max < f[n][i])
        {
            max = f[n][i];
            min = h[n][i];
        }
        else if (max == f[n][i] && h[n][i] < min)
            min = h[n][i];

    std::cout << max << ' ' << min << std::endl;
    return 0;
}