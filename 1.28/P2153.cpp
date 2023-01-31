#include <bits/stdc++.h>

const int maxn = 200;

namespace cflow
{
    const int maxn = ::maxn * 2;

    int n, s, t, h[maxn + 1], dis[maxn + 1], pre[maxn + 1];
    bool inq[maxn + 1];

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

    void init(int _n, int _s, int _t)
    {
        n = _n;
        s = _s;
        t = _t;

        std::fill_n(h + 1, _n, -1);
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
        std::fill_n(dis + 1, n, INT_MAX);
        std::fill_n(inq + 1, n, false);

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
                        q.emplace(e[i].v);
                }
        }

        return dis[t] != INT_MAX;
    }

    std::pair<int, int> EK()
    {
        int flow = 0, cost = 0;

        while (spfa())
        {
            int f = INT_MAX;
            for (int i = t; i != s; i = e[pre[i] ^ 1].v)
                f = std::min(f, e[pre[i]].c);

            flow += f;
            for (int i = t; i != s; i = e[pre[i] ^ 1].v)
            {
                e[pre[i]].c -= f;
                e[pre[i] ^ 1].c += f;
                cost += f * e[pre[i]].w;
            }
        }

        return std::make_pair(flow, cost);
    }
};

int main()
{
    std::freopen("P2153.in", "r", stdin);

    int n, m;
    std::cin >> n >> m;

    cflow::init(n * 2, 1, n * 2);

    for (int i = 1, u, v, w; i <= m; ++i)
    {
        std::cin >> u >> v >> w;
        cflow::add(u + n, v, 1, w);
    }

    cflow::add(1, n + 1, INT_MAX, 0);
    for (int i = 2; i < n; ++i)
        cflow::add(i, n + i, 1, 0);
    cflow::add(n, n * 2, INT_MAX, 0);

    std::pair<int, int> pr = cflow::EK();
    std::cout << pr.first << ' ' << pr.second << std::endl;
    return 0;
}