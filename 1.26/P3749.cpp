#include <bits/stdc++.h>

const int maxn = 100;

int a[maxn + 1], id[maxn + 1][maxn + 1];

namespace flow
{
    const int maxn = ::maxn * 2 + (::maxn + 1) * ::maxn / 2 + 2;

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
    std::freopen("P3749.in", "r", stdin);

    int n;
    bool m;
    std::cin >> n >> m;

    std::vector<int> vct;
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> a[i];
        vct.emplace_back(a[i]);
    }

    std::sort(vct.begin(), vct.end());
    vct.erase(std::unique(vct.begin(), vct.end()), vct.end());

    std::unordered_map<int, int> mid;
    for (std::size_t i = 0; i < vct.size(); ++i)
        mid[vct[i]] = n + i + 1;

    int cnt = n + vct.size();
    for (int i = 1; i <= n; ++i)
        for (int j = i; j <= n; ++j)
        {
            ++cnt;
            id[i][j] = cnt;
        }

    flow::init(cnt);

    for (std::size_t i = 0; i < vct.size(); ++i)
        flow::add(flow::s, n + i + 1, m * vct[i] * vct[i]);

    for (int i = 1; i <= n; ++i)
    {
        flow::add(flow::s, i, a[i]);
        flow::add(mid[a[i]], i, INT_MAX);
        flow::add(i, id[i][i], INT_MAX);
    }

    int sum = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = i, d; j <= n; ++j)
        {
            std::cin >> d;

            if (d <= 0)
                flow::add(flow::s, id[i][j], -d);
            else
            {
                sum += d;
                flow::add(id[i][j], flow::t, d);
            }

            if (i != j)
            {
                flow::add(id[i + 1][j], id[i][j], INT_MAX);
                flow::add(id[i][j - 1], id[i][j], INT_MAX);
            }
        }

    std::cout << sum - flow::dinic() << std::endl;
    return 0;
}