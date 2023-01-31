#include <bits/stdc++.h>

const int maxn = 20;

int sq(int x) { return x * x; }

char c[maxn + 1][maxn + 1];

namespace flow
{
    const int maxn = ::maxn * ::maxn * 2 + 2;

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

int main()
{
    std::freopen("P2472.in", "r", stdin);

    int n, m, lim;
    std::cin >> n >> m >> lim;

    auto calc = [&](int x, int y)
    { return (x - 1) * m + y; };

    flow::init(n * m * 2);

    for (int i = 1; i <= n; ++i)
    {
        std::scanf("%s", c[i] + 1);

        for (int j = 1; j <= m; ++j)
            if (c[i][j] != '0')
            {
                flow::add(calc(i, j), n * m + calc(i, j), c[i][j] - '0');

                if (i <= lim || j <= lim || n - i < lim || m - j < lim)
                    flow::add(n * m + calc(i, j), flow::t, INT_MAX);
            }
    }

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (c[i][j] != '0')
                for (int k = 1; k <= n; ++k)
                    for (int l = 1; l <= m; ++l)
                        if ((i != k || j != l) && c[k][l] != '0' && sq(i - k) + sq(j - l) <= sq(lim))
                            flow::add(n * m + calc(i, j), calc(k, l), INT_MAX);

    int cnt = 0;
    for (int i = 1; i <= n; ++i)
    {
        std::scanf("%s", c[i] + 1);

        for (int j = 1; j <= m; ++j)
            if (c[i][j] == 'L')
            {
                ++cnt;
                flow::add(flow::s, calc(i, j), 1);
            }
    }

    std::cout << cnt - flow::dinic() << std::endl;
    return 0;
}