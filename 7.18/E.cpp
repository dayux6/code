#include <bits/stdc++.h>

int n;
long double ans = 0;

struct edge
{
    int v, w;

    edge(int _v, int _w) : v(_v), w(_w) {}
};
std::vector<edge> *g;

int dfs(int x, int fa)
{
    int siz = 1;
    for (edge e : g[x])
        if (e.v != fa)
        {
            int tmp = dfs(e.v, x);
            ans += (long double)tmp * (n - tmp) * e.w * 6 / n / (n - 1);
            siz += tmp;
        }
    return siz;
}

int main()
{
    freopen("E.in", "r", stdin);
    std::cin >> n;
    g = new std::vector<edge>[n + 1];
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    dfs(1, 0);
    std::cout << std::fixed << std::setprecision(2) << ans << std::endl;
    return 0;
}