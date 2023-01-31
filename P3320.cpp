#include <bits/stdc++.h>

const int maxn = 1e5, maxlg = 16;

int lg, dfc, dfn[maxn + 1], dep[maxn + 1], anc[maxn + 1][maxlg + 1];
long long w[maxn + 1];

struct edge
{
    int v, w;

    edge(int _v, int _w) : v(_v), w(_w) {}
};
std::vector<edge> g[maxn + 1];

void dfs(int x)
{
    ++dfc;
    dfn[x] = dfc;

    for (int i = 1; i <= lg; ++i)
        anc[x][i] = anc[anc[x][i - 1]][i - 1];

    for (edge e : g[x])
        if (e.v ^ anc[x][0])
        {
            dep[e.v] = dep[x] + 1;
            w[e.v] = w[x] + e.w;
            anc[e.v][0] = x;
            dfs(e.v);
        }
}

int getlca(int x, int y)
{
    if (dep[x] < dep[y])
        std::swap(x, y);
    while (dep[x] > dep[y])
        x = anc[x][(int)log2(dep[x] - dep[y])];

    if (x == y)
        return x;

    for (int i = lg; i >= 0; --i)
        if (anc[x][i] ^ anc[y][i])
        {
            x = anc[x][i];
            y = anc[y][i];
        }
    return anc[x][0];
}

long long getdis(int x, int y) { return w[x] + w[y] - w[getlca(x, y)] * 2; }

int main()
{
    freopen("P3320.in", "r", stdin);
    int n, m;
    std::cin >> n >> m;

    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    lg = log2(n);
    dfs(1);

    long long res = 0;
    std::set<std::pair<int, int>> s;
    for (int i = 0; i < m; ++i)
    {
        int x;
        std::cin >> x;
        if (s.count(std::make_pair(dfn[x], x)))
        {
            int u = 0, v = 0;
            auto it = s.lower_bound(std::make_pair(dfn[x], x));
            if (it != s.begin())
            {
                --it;
                u = it->second;
                res -= getdis(x, u);
                ++it;
            }
            ++it;
            if (it != s.end())
            {
                v = it->second;
                res -= getdis(x, v);
            }
            --it;
            if (u && v)
                res += getdis(u, v);
            s.erase(it);
        }
        else
        {
            int u = 0, v = 0;
            auto it = s.lower_bound(std::make_pair(dfn[x], 0));
            if (it != s.end())
            {
                u = it->second;
                res += getdis(x, it->second);
            }
            if (it != s.begin())
            {
                --it;
                v = it->second;
                res += getdis(x, it->second);
                ++it;
            }
            if (u && v)
                res -= getdis(u, v);
            s.emplace(dfn[x], x);
        }

        if (s.size() >= 2)
            std::cout << res + getdis(s.begin()->second, s.rbegin()->second) << std::endl;
        else
            std::cout << 0 << std::endl;
    }
    return 0;
}