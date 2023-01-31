#include <bits/stdc++.h>

const int maxn = 40, maxm = 100, maxp = 800, maxlim = 1e6;

int tot, s, t, p[maxn + 1], T[maxn + 1][maxm + 1], id[maxlim + 1], c[maxlim + 1], h[maxlim + 2], dis[maxlim + 2], pre[maxlim + 2];
bool inq[maxlim + 2];

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
    std::fill_n(dis, maxlim + 2, INT_MAX);
    std::fill_n(inq, maxlim + 2, false);

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

int main()
{
    std::freopen("P2050.in", "r", stdin);

    int n, m;
    std::cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        std::cin >> p[i];

    s = 0;
    t = maxlim + 1;

    std::fill_n(h, maxlim + 2, -1);
    for (int i = 1; i <= n; ++i)
    {
        add(s, i, p[i], 0);

        for (int j = 1; j <= m; ++j)
        {
            std::cin >> T[i][j];
            add(i, n + j, 1, T[i][j]);
            id[n + j] = j;
            c[n + j] = 1;
        }
    }
    for (int i = 1; i <= m; ++i)
        add(n + i, t, 1, 0);

    tot = n + m;
    int ans = 0;
    while (spfa())
    {
        ++tot;
        int f = INT_MAX;
        for (int x = t; x != s; x = e[pre[x] ^ 1].v)
        {
            if (x > n && x != t && id[tot] == 0)
            {
                id[tot] = id[x];
                c[tot] = c[x] + 1;
            }

            f = std::min(f, e[pre[x]].c);
        }

        for (int x = t; x != s; x = e[pre[x] ^ 1].v)
        {
            e[pre[x]].c -= f;
            e[pre[x] ^ 1].c += f;
            ans += f * e[pre[x]].w;
        }

        add(tot, t, 1, 0);
        for (int i = 1; i <= n; ++i)
            add(i, tot, 1, T[i][id[tot]] * c[tot]);
    }

    std::cout << ans << std::endl;
    return 0;
}