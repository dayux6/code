#include <bits/stdc++.h>

const int maxn = 2e5, maxm = 2e5;

struct edge
{
    int u, v, w;

    bool operator<(edge rhs) const { return w < rhs.w; }
} e[maxm];

class DSU
{
private:
    int fa[maxn + 1];

    int find(int x)
    {
        while (x != fa[x])
            x = fa[x] = fa[fa[x]];
        return x;
    }

public:
    void build(int n) { std::iota(fa + 1, fa + n + 1, 1); }

    void merge(int x, int y) { fa[find(x)] = find(y); }

    bool query(int x, int y) { return find(x) == find(y); }
} dsu;

int n, cnt;
bool vis[maxn + 1], flg[maxm];
std::unordered_set<int> unvis, g[maxn + 1];

void bfs(int x)
{
    std::queue<int> q({x});
    vis[x] = true;
    unvis.erase(x);
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        for (std::unordered_set<int>::iterator it = unvis.begin(); it != unvis.end();)
        {
            int v = *it;
            ++it;
            if (g[x].count(v) == 0)
            {
                ++cnt;
                vis[v] = true;
                unvis.erase(v);
                dsu.merge(x, v);
                q.push(v);
            }
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    std::freopen("CF1508E.in", "r", stdin);
#endif

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int m;
    std::cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        g[i].insert(i);
    int xsum = 0;
    for (int i = 0; i < m; ++i)
    {
        std::cin >> e[i].u >> e[i].v >> e[i].w;
        g[e[i].u].insert(e[i].v);
        g[e[i].v].insert(e[i].u);
        xsum ^= e[i].w;
    }

    dsu.build(n);
    for (int i = 1; i <= n; ++i)
        unvis.insert(i);
    for (int i = 1; i <= n; ++i)
        if (!vis[i])
            bfs(i);

    std::sort(e, e + m);
    long long sum = 0;
    for (int i = 0; i < m; ++i)
        if (!dsu.query(e[i].u, e[i].v))
        {
            flg[i] = true;
            dsu.merge(e[i].u, e[i].v);
            sum += e[i].w;
        }

    if (1ll * n * (n - 1) / 2 - m - cnt == 0)
    {
        dsu.build(n);

        for (int i = 0; i < m; ++i)
            if (!dsu.query(e[i].u, e[i].v))
            {
                dsu.merge(e[i].u, e[i].v);

                if (!flg[i])
                {
                    std::cout << sum + std::min(xsum, e[i].w) << std::endl;
                    return 0;
                }
            }

        std::cout << sum + xsum << std::endl;
    }
    else
        std::cout << sum << std::endl;
    return 0;
}