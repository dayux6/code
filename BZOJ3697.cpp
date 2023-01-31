#include <bits/stdc++.h>

const int maxn = 1e5;

int siz[maxn + 1], gc, tot, min;
long long ans;
bool vis[maxn + 1];
std::unordered_map<int, int> tmp, cnt[2];

struct edge
{
    int v, w;

    edge(int _v, bool _w) : v(_v)
    {
        if (_w)
            w = 1;
        else
            w = -1;
    }
};
std::vector<edge> g[maxn + 1];

void getsiz(int x, int fa)
{
    siz[x] = 1;
    for (edge e : g[x])
        if (!vis[e.v] && e.v ^ fa)
        {
            getsiz(e.v, x);
            siz[x] += siz[e.v];
        }
}

void getgc(int x, int fa)
{
    int w = tot - siz[x];
    for (edge e : g[x])
        if (!vis[e.v] && e.v ^ fa)
        {
            getgc(e.v, x);
            w = std::max(w, siz[e.v]);
        }

    if (w < min)
    {
        gc = x;
        min = w;
    }
}

int getrt(int x)
{
    getsiz(x, 0);
    tot = min = siz[x];
    getgc(x, 0);
    return gc;
}

void getdis(int x, int fa, int w)
{
    if (tmp[w])
        ++cnt[1][w];
    else
        ++cnt[0][w];
    ++tmp[w];

    for (edge e : g[x])
        if (!vis[e.v] && e.v ^ fa)
            getdis(e.v, x, w + e.w);

    --tmp[w];
}

void calc(int x)
{
    std::unordered_map<int, int> pre[2];

    for (edge e : g[x])
        if (!vis[e.v])
        {
            for (int i = 0; i < 2; ++i)
                cnt[i].clear();
            getdis(e.v, x, e.w);

            ans += cnt[1][0] + 1ll * pre[0][0] * cnt[0][0];
            for (std::pair<int, int> pr : cnt[0])
                ans += 1ll * pre[1][-pr.first] * pr.second;
            for (std::pair<int, int> pr : cnt[1])
                ans += 1ll * (pre[0][-pr.first] + pre[1][-pr.first]) * pr.second;

            for (int i = 0; i < 2; ++i)
                for (std::pair<int, int> pr : cnt[i])
                    pre[i][pr.first] += pr.second;
        }
}

void divide(int x)
{
    vis[x] = true;
    calc(x);

    for (edge e : g[x])
        if (!vis[e.v])
            divide(getrt(e.v));
}

int main()
{
    freopen("BZOJ3697.in", "r", stdin);
    int n;
    std::cin >> n;

    for (int i = 1; i < n; ++i)
    {
        int u, v;
        bool w;
        std::cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    divide(getrt(1));

    std::cout << ans << std::endl;
    return 0;
}