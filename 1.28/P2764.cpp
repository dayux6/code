#include <bits/stdc++.h>

const int maxn = 500;

namespace flow
{
    const int maxn = ::maxn * 2 + 2;

    int n, s, t, h[maxn], cur[maxn], dep[maxn];

    struct edge
    {
        int v, w, p;

        edge(int _v, int _w, int _p)
        {
            v = _v;
            w = _w;
            p = _p;
        }
    };
    std::vector<edge> e;

    void init(int _n)
    {
        s = 0;
        t = _n + 1;
        n = _n + 2;

        std::fill_n(h, n, -1);
    }

    void addedge(int u, int v, int w)
    {
        e.emplace_back(v, w, h[u]);
        h[u] = e.size() - 1;
    }

    void add(int u, int v, int w)
    {
        addedge(u, v, w);
        addedge(v, u, 0);
    }

    bool bfs()
    {
        std::copy_n(h, n, cur);
        std::fill_n(dep, n, -1);

        dep[s] = 0;
        std::queue<int> q;
        q.emplace(s);

        while (!q.empty())
        {
            int x = q.front();
            q.pop();

            for (int i = h[x]; i != -1; i = e[i].p)
                if (e[i].w != 0 && dep[e[i].v] == -1)
                {
                    dep[e[i].v] = dep[x] + 1;
                    q.emplace(e[i].v);
                }
        }

        return dep[t] != -1;
    }

    int dfs(int x, int f)
    {
        if (x == t || f == 0)
            return f;

        int rest = f;
        for (int &i = cur[x]; i != -1; i = e[i].p)
            if (dep[e[i].v] == dep[x] + 1)
            {
                int tmp = dfs(e[i].v, std::min(rest, e[i].w));

                rest -= tmp;
                e[i].w -= tmp;
                e[i ^ 1].w += tmp;

                if (rest == 0)
                    break;
            }

        return f - rest;
    }

    int dinic()
    {
        int ret = 0;

        while (bfs())
            ret += dfs(s, INT_MAX);

        return ret;
    }
};

namespace dsu
{
    int fa[maxn + 1];
    std::vector<int> bel[maxn + 1];

    void init(int n)
    {
        std::iota(fa + 1, fa + n + 1, 1);
        for (int i = 1; i <= n; ++i)
            bel[i].emplace_back(i);
    }

    int find(int x)
    {
        if (x != fa[x])
            fa[x] = find(fa[x]);
        return fa[x];
    }

    void merge(int x, int y)
    {
        int u = find(x), v = find(y);

        if (u != v)
        {
            if (bel[u].size() < bel[v].size())
                std::swap(u, v);

            fa[v] = u;
            for (int i : bel[v])
                bel[u].emplace_back(i);

            std::vector<int>().swap(bel[v]);
        }
    }
};

int main()
{
    std::freopen("P2764.in", "r", stdin);

    int n, m;
    std::cin >> n >> m;

    flow::init(n * 2);

    for (int i = 1; i <= n; ++i)
    {
        flow::add(flow::s, i, 1);
        flow::add(n + i, flow::t, 1);
    }

    for (int i = 0, u, v; i < m; ++i)
    {
        std::cin >> u >> v;
        flow::add(u, n + v, 1);
    }

    int min = n - flow::dinic();

    dsu::init(n);
    for (int x = 1; x <= n; ++x)
        for (int i = flow::h[x]; i != -1; i = flow::e[i].p)
            if (i % 2 == 0 && flow::e[i].w == 0)
                dsu::merge(x, flow::e[i].v - n);

    for (int i = 1; i <= n; ++i)
        if (i == dsu::find(i))
        {
            for (int x : dsu::bel[i])
                std::cout << x << ' ';
            std::cout << '\n';
        }

    std::cout << min << std::endl;
    return 0;
}