#include <bits/stdc++.h>

typedef unsigned long long ull;

int bls, blc, *bel, **con, *siz, dfc, *dfn;
std::vector<int> *g;

class BIT
{
private:
    int n;
    ull *t;
    int lowbit(int);

public:
    BIT(int);
    void modify(int, int);
    ull query(int);
};

BIT::BIT(int _n) : n(_n), t(new ull[_n + 1]()) {}

int BIT::lowbit(int x) { return x & -x; }

void BIT::modify(int x, int v)
{
    for (int i = x; i <= n; i += lowbit(i))
        t[i] += v;
}

ull BIT::query(int x)
{
    ull ret = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        ret += t[i];
    return ret;
}

void dfs(int x, int fa)
{
    for (int i = 0; i <= blc; ++i)
        con[x][i] = con[fa][i];
    ++con[x][bel[x]];
    siz[x] = 1;
    ++dfc;
    dfn[x] = dfc;
    for (int v : g[x])
        if (v ^ fa)
        {
            dfs(v, x);
            siz[x] += siz[v];
        }
}

int main()
{
    freopen("BZOJ4765.in", "r", stdin);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    int *d = new int[n + 1];
    for (int i = 1; i <= n; ++i)
        std::cin >> d[i];
    g = new std::vector<int>[n + 1];
    int rt;
    for (int i = 1; i <= n; ++i)
    {
        int u, v;
        std::cin >> u >> v;
        if (u == 0)
            rt = v;
        else
        {
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
    }
    bls = sqrt(n);
    bel = new int[n + 1];
    for (int i = 1; i <= n; ++i)
        bel[i] = (i - 1) / bls;
    blc = bel[n];
    con = new int *[n + 1];
    for (int i = 0; i <= n; ++i)
        con[i] = new int[blc + 1]();
    siz = new int[n + 1];
    dfn = new int[n + 1];
    dfs(rt, 0);
    BIT t(n);
    for (int i = 1; i <= n; ++i)
        t.modify(dfn[i], d[i]);
    ull *ans = new ull[blc + 1]();
    for (int i = 0; i <= blc; ++i)
        for (int j = i * bls + 1; j <= std::min((i + 1) * bls, n); ++j)
            ans[i] += t.query(dfn[j] + siz[j] - 1) - t.query(dfn[j] - 1);
    for (int i = 0; i < m; ++i)
    {
        int op;
        std::cin >> op;
        switch (op)
        {
        case 1:
        {
            int u, v;
            std::cin >> u >> v;
            for (int j = 0; j <= blc; ++j)
                ans[j] += 1ull * (v - d[u]) * con[u][j];
            t.modify(dfn[u], v - d[u]);
            d[u] = v;
            break;
        }
        case 2:
        {
            int l, r;
            std::cin >> l >> r;
            ull res = 0;
            if (bel[l] == bel[r])
                for (int i = l; i <= r; ++i)
                    res += t.query(dfn[i] + siz[i] - 1) - t.query(dfn[i] - 1);
            else
            {
                for (int i = l; i <= (bel[l] + 1) * bls; ++i)
                    res += t.query(dfn[i] + siz[i] - 1) - t.query(dfn[i] - 1);
                for (int i = bel[r] * bls + 1; i <= r; ++i)
                    res += t.query(dfn[i] + siz[i] - 1) - t.query(dfn[i] - 1);
                for (int i = bel[l] + 1; i < bel[r]; ++i)
                    res += ans[i];
            }
            std::cout << res << '\n';
            break;
        }
        }
    }
    return 0;
}