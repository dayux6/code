#include <bits/stdc++.h>

const int maxn = 1e5, maxlg = 16;

int n, dep[maxn + 1], siz[maxn + 1], hs[maxn + 1], anc[maxn + 1][maxlg + 1], top[maxn + 1], dfc, dfn[maxn + 1], f[maxn + 1], h[maxn + 1];
std::vector<int> g[maxn + 1];

struct route
{
    int u, v, w;

    route(int _u, int _v, int _w)
    {
        u = _u;
        v = _v;
        w = _w;
    }
};
std::vector<route> r[maxn + 1];

class BIT
{
private:
    int t[maxn + 1];

    int lowbit(int x) { return x & -x; }

public:
    BIT() { std::fill_n(t + 1, n, 0); }

    void modify(int x, int v)
    {
        for (int i = x; i <= n; i += lowbit(i))
            t[i] += v;
    }

    int query(int x)
    {
        int ret = 0;
        for (int i = x; i > 0; i -= lowbit(i))
            ret += t[i];
        return ret;
    }
} t;

void dfs(int x)
{
    siz[x] = 1;
    for (int i = 1; i <= maxlg; ++i)
        anc[x][i] = anc[anc[x][i - 1]][i - 1];

    for (int v : g[x])
        if (v != anc[x][0])
        {
            dep[v] = dep[x] + 1;
            anc[v][0] = x;
            dfs(v);
            siz[x] += siz[v];

            if (hs[x] == 0 || siz[v] > siz[hs[x]])
                hs[x] = v;
        }
}

void dfs(int x, int t)
{
    top[x] = t;
    ++dfc;
    dfn[x] = dfc;

    if (hs[x] != 0)
    {
        dfs(hs[x], t);

        for (int v : g[x])
            if (v != anc[x][0] && v != hs[x])
                dfs(v, v);
    }
}

int getlca(int x, int y)
{
    if (dep[x] < dep[y])
        std::swap(x, y);
    while (dep[x] > dep[y])
        x = anc[x][(int)std::log2(dep[x] - dep[y])];

    if (x == y)
        return x;
    for (int i = maxlg; i >= 0; --i)
        if (anc[x][i] != anc[y][i])
        {
            x = anc[x][i];
            y = anc[y][i];
        }
    return anc[x][0];
}

int getanc(int x, int k)
{
    for (int i = maxlg; i >= 0; --i)
        if ((k >> i) & 1)
            x = anc[x][i];
    return x;
}

int getsum(int u, int x)
{
    int ret = 0;
    while (top[x] != top[u])
    {
        ret += h[hs[x]] + t.query(dfn[x]) - t.query(dfn[top[x]] - 1) - h[top[x]];
        x = anc[top[x]][0];
    }
    return ret + h[hs[x]] + t.query(dfn[x]) - t.query(dfn[u] - 1);
}

void dp(int x)
{
    for (int v : g[x])
        if (v != anc[x][0])
        {
            dp(v);
            f[x] += h[v];
        }

    h[x] = f[x];
    t.modify(dfn[x], f[x] - h[hs[x]]);
    for (route cur : r[x])
    {
        if (cur.u == x && cur.v == x)
            h[x] = std::max(h[x], f[x] + cur.w);
        else if (cur.u == x)
        {
            int sub = getanc(cur.v, dep[cur.v] - dep[x] - 1);
            h[x] = std::max(h[x], f[x] - h[sub] + getsum(sub, cur.v) + cur.w);
        }
        else
        {
            int subu = getanc(cur.u, dep[cur.u] - dep[x] - 1), subv = getanc(cur.v, dep[cur.v] - dep[x] - 1);
            h[x] = std::max(h[x], f[x] - h[subu] - h[subv] + getsum(subu, cur.u) + getsum(subv, cur.v) + cur.w);
        }
    }
}

int main()
{
    std::freopen("paths.in", "r", stdin);
    std::freopen("paths.out", "w", stdout);

    int m;
    std::cin >> n >> m;

    for (int i = 1; i < n; ++i)
    {
        int u, v;
        std::cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }

    dfs(1);
    dfs(1, 1);

    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        std::cin >> u >> v >> w;

        if (dep[u] > dep[v])
            std::swap(u, v);

        int lca = getlca(u, v);
        r[lca].emplace_back(u, v, w);
    }

    dp(1);

    std::cout << h[1] << std::endl;
    return 0;
}