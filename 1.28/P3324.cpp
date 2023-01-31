#include <bits/stdc++.h>

typedef long double db;

const int maxn = 50;
const db eps = 1e-6;

int a[maxn + 1], b[maxn + 1];
bool e[maxn + 1][maxn + 1];

namespace flow
{
    const int maxn = ::maxn * 2 + 2;

    int n, s, t, h[maxn], cur[maxn], dep[maxn];

    struct edge
    {
        int v, p;
        db w;

        edge(int _v, db _w, int _p)
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
        std::vector<edge>().swap(e);
    }

    void addedge(int u, int v, db w)
    {
        e.emplace_back(v, w, h[u]);
        h[u] = e.size() - 1;
    }

    void add(int u, int v, db w)
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
                if (e[i].w > 0 && dep[e[i].v] == -1)
                {
                    dep[e[i].v] = dep[x] + 1;
                    q.emplace(e[i].v);
                }
        }

        return dep[t] != -1;
    }

    db dfs(int x, db f)
    {
        if (x == t || f == 0)
            return f;

        db rest = f, ret = 0;
        for (int &i = cur[x]; i != -1; i = e[i].p)
            if (dep[e[i].v] == dep[x] + 1)
            {
                db tmp = dfs(e[i].v, std::min(rest, e[i].w));

                rest -= tmp;
                ret += tmp;
                e[i].w -= tmp;
                e[i ^ 1].w += tmp;

                if (rest == 0)
                    break;
            }

        return ret;
    }

    db dinic()
    {
        db ret = 0;

        while (bfs())
            ret += dfs(s, INFINITY);

        return ret;
    }
};

int main()
{
    std::freopen("P3324.in", "r", stdin);

    int n, m;
    std::cin >> n >> m;

    int sum = 0;
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> a[i];
        sum += a[i];
    }
    for (int i = 1; i <= m; ++i)
        std::cin >> b[i];
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            std::cin >> e[i][j];

    auto check = [&](db k)
    {
        flow::init(n + m);

        for (int i = 1; i <= n; ++i)
            flow::add(flow::s, i, a[i]);
        for (int i = 1; i <= m; ++i)
        {
            flow::add(n + i, flow::t, k * b[i]);

            for (int j = 1; j <= n; ++j)
                if (e[i][j])
                    flow::add(j, n + i, INFINITY);
        }

        return flow::dinic() == sum;
    };

    db l = 0, r = sum;
    while (r - l >= eps)
    {
        db mid = (l + r) / 2;

        if (check(mid))
            r = mid;
        else
            l = mid;
    }

    std::cout << std::fixed << (l + r) / 2 << std::endl;
    return 0;
}