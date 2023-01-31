#include <bits/stdc++.h>

#define int long long

const int maxn = 200;

int a[maxn + 1], b[maxn + 1], c[maxn + 1], s[maxn + 1];

namespace cflow
{
    const int maxn = ::maxn + 2;

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
        std::fill_n(dis, n, LLONG_MIN);
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
                if (e[i].c != 0 && dis[e[i].v] < dis[x] + e[i].w)
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

        return dis[t] != LLONG_MIN;
    }

    int EK()
    {
        int flow = 0, cost = 0;

        while (spfa())
        {
            int f = INT_MAX, sum = 0;
            for (int i = t; i != s; i = e[pre[i] ^ 1].v)
            {
                f = std::min(f, e[pre[i]].c);
                sum += e[pre[i]].w;
            }

            bool b = false;
            if (cost + f * sum < 0)
            {
                f = cost / -sum;
                b = true;
            }

            flow += f;
            cost += f * sum;
            for (int i = t; i != s; i = e[pre[i] ^ 1].v)
            {
                e[pre[i]].c -= f;
                e[pre[i] ^ 1].c += f;
            }

            if (b)
                break;
        }
        return flow;
    }

};

signed main()
{
    std::freopen("P4068.in", "r", stdin);

    int n;
    std::cin >> n;

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> a[i];

        int tmp = a[i];
        for (int j = 2; j * j <= tmp; ++j)
            while (tmp % j == 0)
            {
                ++s[i];
                tmp /= j;
            }
        if (tmp != 1)
            ++s[i];
    }

    for (int i = 1; i <= n; ++i)
        std::cin >> b[i];
    for (int i = 1; i <= n; ++i)
        std::cin >> c[i];

    cflow::init(n);

    for (int i = 1; i <= n; ++i)
        if (s[i] & 1)
            for (int j = 1; j <= n; ++j)
                if ((a[i] % a[j] == 0 && s[i] == s[j] + 1) || (a[j] % a[i] == 0 && s[j] == s[i] + 1))
                    cflow::add(i, j, INT_MAX, c[i] * c[j]);
    for (int i = 1; i <= n; ++i)
        if (s[i] & 1)
            cflow::add(cflow::s, i, b[i], 0);
        else
            cflow::add(i, cflow::t, b[i], 0);

    std::cout << cflow::EK() << std::endl;
    return 0;
}