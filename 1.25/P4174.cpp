#include <bits/stdc++.h>

const int maxn = 5e3, maxm = 5e4;

namespace flow
{
    const int maxn = ::maxn + ::maxm + 2;

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
        n = t + 1;

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

int main()
{
    std::freopen("P4174.in", "r", stdin);

    int n, m;
    std::cin >> n >> m;

    flow::init(n + m);

    for (int i = 1, p; i <= n; ++i)
    {
        std::cin >> p;

        flow::add(flow::s, i, p);
    }

    int sum = 0;
    for (int i = 1, u, v, w; i <= m; ++i)
    {
        std::cin >> u >> v >> w;
        sum += w;

        flow::add(u, n + i, INT_MAX);
        flow::add(v, n + i, INT_MAX);
        flow::add(n + i, flow::t, w);
    }

    std::cout << sum - flow::dinic() << std::endl;
    return 0;
}