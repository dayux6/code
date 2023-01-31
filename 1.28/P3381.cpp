#include <bits/stdc++.h>

const int maxn = 5e3;

namespace cflow
{
    int n, s, t, h[maxn + 1], dis[maxn + 1], pre[maxn + 1];
    bool inq[maxn + 1];

    struct edge
    {
        int v, w, c, p;

        edge(int _v, int _w, int _c, int _p)
        {
            v = _v;
            w = _w;
            c = _c;
            p = _p;
        }
    };
    std::vector<edge> e;

    void init(int _n, int _s, int _t)
    {
        s = _s;
        t = _t;
        n = _n;

        std::fill_n(h + 1, n, -1);
    }

    void addedge(int u, int v, int w, int c)
    {
        e.emplace_back(v, w, c, h[u]);
        h[u] = e.size() - 1;
    }

    void add(int u, int v, int w, int c)
    {
        addedge(u, v, w, c);
        addedge(v, u, 0, -c);
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
                if (e[i].w != 0 && dis[e[i].v] > dis[x] + e[i].c)
                {
                    dis[e[i].v] = dis[x] + e[i].c;
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
                f = std::min(f, e[pre[i]].w);

            flow += f;
            for (int i = t; i != s; i = e[pre[i] ^ 1].v)
            {
                e[pre[i]].w -= f;
                e[pre[i] ^ 1].w += f;
                cost += f * e[pre[i]].c;
            }
        }

        return std::make_pair(flow, cost);
    }
};

int main()
{
    std::freopen("P3381.in", "r", stdin);

    int n, m, s, t;
    std::cin >> n >> m >> s >> t;

    cflow::init(n, s, t);

    for (int i = 0, u, v, w, c; i < m; ++i)
    {
        std::cin >> u >> v >> w >> c;
        cflow::add(u, v, w, c);
    }

    std::pair<int, int> pr = cflow::EK();
    std::cout << pr.first << ' ' << pr.second << std::endl;
    return 0;
}