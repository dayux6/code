#include <bits/stdc++.h>

const int maxm = 9, maxn = 60;

namespace cflow
{
    const int maxn = ::maxn + ::maxm * ::maxn + 2;

    int n, s, t, h[maxn], dis[maxn], pre[maxn];
    bool inq[maxn];

    struct edge
    {
        int v, c, w, p;

        edge(int _v, int _c, int _w, int _p)
        {
            v = _v;
            c = _c;
            w = _w;
            p = _p;
        }
    };
    std::vector<edge> e;

    void init(int _n)
    {
        n = _n + 2;
        s = 0;
        t = _n + 1;

        std::fill_n(h, n, -1);
    }

    void addedge(int u, int v, int c, int w)
    {
        e.emplace_back(v, c, w, h[u]);
        h[u] = e.size() - 1;
    }

    void add(int u, int v, int c, int w)
    {
        addedge(u, v, c, w);
        addedge(v, u, 0, -w);
    }

    bool spfa()
    {
        std::fill_n(dis, n, INT_MAX);
        std::fill_n(inq, n, false);

        dis[s] = 0;
        inq[s] = true;
        std::queue<int> q;
        q.emplace(s);

        while (!q.empty())
        {
            int x = q.front();
            q.pop();
            inq[x] = false;

            for (int i = h[x]; i != -1; i = e[i].p)
                if (e[i].c != 0 && dis[e[i].v] > dis[x] + e[i].w)
                {
                    dis[e[i].v] = dis[x] + e[i].w;
                    pre[e[i].v] = i;

                    if (!inq[e[i].v])
                    {
                        inq[e[i].v] = true;
                        q.emplace(e[i].v);
                    }
                }
        }

        return dis[t] != INT_MAX;
    }

    int EK()
    {
        int cost = 0;

        while (spfa())
        {
            int f = INT_MAX;
            for (int i = t; i != s; i = e[pre[i] ^ 1].v)
                f = std::min(f, e[pre[i]].c);

            for (int i = t; i != s; i = e[pre[i] ^ 1].v)
            {
                e[pre[i]].c -= f;
                e[pre[i] ^ 1].c += f;
                cost += f * e[pre[i]].w;
            }
        }

        return cost;
    }
};

int main()
{
    std::freopen("P2053.in", "r", stdin);

    int m, n;
    std::cin >> m >> n;

    cflow::init(n + m * n);
    for (int i = 1; i <= n; ++i)
        cflow::add(cflow::s, i, 1, 0);
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            cflow::add(n + (i - 1) * n + j, cflow::t, 1, 0);

    for (int i = 1; i <= n; ++i)
        for (int j = 1, t; j <= m; ++j)
        {
            std::cin >> t;

            for (int k = 1; k <= n; ++k)
                cflow::add(i, n + (j - 1) * n + k, 1, k * t);
        }

    std::cout << std::fixed << std::setprecision(2) << (long double)cflow::EK() / n << std::endl;
    return 0;
}