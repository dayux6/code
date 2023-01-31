#include <bits/stdc++.h>

const int maxn = 20, maxm = 30;

int val[maxn * maxm + 1];

namespace flow
{
    const int maxn = ::maxn * ::maxm + 2;

    int n, s, t, h[maxn], cur[maxn], dep[maxn];
    bool flg[maxn];

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
        std::fill_n(flg, n, false);
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
                if (flg[e[i].v] && e[i].w != 0 && dep[e[i].v] == -1)
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
            if (flg[e[i].v] && dep[e[i].v] == dep[x] + 1)
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

void topo()
{
    using namespace flow;

    static int ind[flow::maxn];

    for (int x = 0; x < n; ++x)
        for (int i = h[x]; i != -1; i = e[i].p)
            if (i % 2 == 0)
                ++ind[e[i].v];

    std::queue<int> q;
    for (int i = 0; i < n; ++i)
        if (ind[i] == 0)
            q.emplace(i);

    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        flg[x] = true;

        for (int i = h[x]; i != -1; i = e[i].p)
            if (i % 2 == 0)
            {
                --ind[e[i].v];

                if (ind[e[i].v] == 0)
                    q.emplace(e[i].v);
            }
    }
}

int main()
{
    std::freopen("P2805.in", "r", stdin);

    int n, m;
    std::cin >> n >> m;

    flow::init(n * m);

    auto calc = [&](int x, int y)
    { return (x - 1) * m + y; };

    for (int i = 1; i <= n; ++i)
        for (int j = 1, c; j <= m; ++j)
        {
            int id = calc(i, j);

            std::cin >> val[id] >> c;

            if (val[id] >= 0)
                flow::add(id, flow::t, val[id]);
            else
                flow::add(flow::s, id, -val[id]);

            if (j < m)
                flow::add(calc(i, j + 1), id, INT_MAX);
            for (int k = 0, x, y; k < c; ++k)
            {
                std::cin >> x >> y;
                flow::add(id, calc(x + 1, y + 1), INT_MAX);
            }
        }

    topo();

    int sum = 0;
    for (int i = 1; i <= n * m; ++i)
        if (flow::flg[i] && val[i] > 0)
            sum += val[i];

    flow::flg[flow::t] = true;
    std::cout << sum - flow::dinic() << std::endl;
    return 0;
}