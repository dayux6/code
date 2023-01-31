#include <bits/stdc++.h>

const int maxn = 50;

bool flg[maxn + 1];
std::vector<int> pre[maxn + 1];

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

int main()
{
    std::freopen("P2762.in", "r", stdin);

    int m, n;
    std::cin >> m >> n;

    flow::init(m + n);

    int sum = 0;
    std::string str;
    for (int i = 1, w; i <= m; ++i)
    {
        std::cin >> w >> std::ws;
        sum += w;
        flow::add(n + i, flow::t, w);

        std::getline(std::cin, str);
        int x = 0;
        for (char c : str)
            if (isdigit(c))
                x = x * 10 + (c ^ 48);
            else
            {
                pre[i].emplace_back(x);
                flow::add(x, n + i, INT_MAX);
                x = 0;
            }

        if (x != 0)
        {
            pre[i].emplace_back(x);
            flow::add(x, n + i, INT_MAX);
        }
    }

    for (int i = 1, w; i <= n; ++i)
    {
        std::cin >> w;
        flow::add(flow::s, i, w);
    }

    int max = sum - flow::dinic();

    for (int i = 1; i <= n; ++i)
        if (flow::dep[i] == -1)
            flg[i] = true;

    for (int i = 1; i <= m; ++i)
    {
        bool b = true;

        for (int v : pre[i])
            if (!flg[v])
            {
                b = false;
                break;
            }

        if (b)
            std::cout << i << ' ';
    }
    std::cout << std::endl;

    for (int i = 1; i <= n; ++i)
        if (flg[i])
            std::cout << i << ' ';
    std::cout << std::endl
              << max << std::endl;
    return 0;
}