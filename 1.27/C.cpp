#include <bits/stdc++.h>

const int maxk = 1e5;

int n;
long long dep[maxk * 2 + 1];
bool vis[maxk * 2 + 1];
std::vector<int> vct;

struct edge
{
    int v, w;

    edge(int _v, int _w)
    {
        v = _v;
        w = _w;
    }
};
std::vector<edge> g[maxk * 2 + 1];

namespace dsu
{
    int fa[maxk * 2 + 1];

    void build(int n) { std::iota(fa + 1, fa + n + 1, 1); }

    int find(int x)
    {
        if (x != fa[x])
            fa[x] = find(fa[x]);
        return fa[x];
    }

    void merge(int x, int y) { fa[find(y)] = find(x); }
};

bool dfs(int x)
{
    vis[x] = true;
    vct.emplace_back(x);

    for (edge e : g[x])
        if (!vis[e.v])
        {
            dep[e.v] = dep[x] + e.w;
            if (!dfs(e.v))
                return false;
        }
        else if (dep[e.v] != dep[x] + e.w)
            return false;

    return true;
}

bool check(int x)
{
    std::vector<int>().swap(vct);

    if (!dfs(x))
        return false;

    std::sort(vct.begin(), vct.end(), [&](int x, int y)
              { return dep[x] > dep[y]; });

    for (std::size_t i = 0; i < vct.size(); ++i)
        for (edge e : g[vct[i]])
            if (e.w > 0)
            {
                int u = dsu::find(vct[i]), v = dsu::find(e.v);

                if (u != v)
                {
                    if (dep[u] == dep[v])
                        return false;

                    if (dep[u] < dep[v])
                        dsu::merge(u, v);
                    else
                        dsu::merge(v, u);
                }
            }

    return true;
}

bool solve()
{
    int k;
    std::cin >> k;

    n = 0;
    std::unordered_map<int, int> id;
    for (int i = 0, u, v, w; i < k; ++i)
    {
        std::cin >> u >> v >> w;

        if (id.count(u) == 0)
        {
            ++n;
            std::vector<edge>().swap(g[n]);
            id.emplace(u, n);
        }
        if (id.count(v) == 0)
        {
            ++n;
            std::vector<edge>().swap(g[n]);
            id.emplace(v, n);
        }

        g[id[u]].emplace_back(id[v], w);
        g[id[v]].emplace_back(id[u], -w);
    }

    std::fill_n(vis + 1, n, false);
    dsu::build(n);
    for (int i = 1; i <= n; ++i)
        if (!vis[i])
            if (!check(i))
                return false;

    return true;
}

int main()
{
    std::freopen("tree.in", "r", stdin);
    std::freopen("tree.out", "w", stdout);

    int t;
    std::cin >> t;

    for (int i = 0; i < t; ++i)
        std::cout << (solve() ? "Yes" : "No") << std::endl;
    return 0;
}