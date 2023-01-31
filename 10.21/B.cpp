#include <bits/stdc++.h>

void read(int &x)
{
    x = 0;
    char c = std::getchar();

    while (!std::isdigit(c))
        c = std::getchar();
    while (std::isdigit(c))
    {
        x = x * 10 + (c ^ 48);
        c = std::getchar();
    }
}

void write(int x)
{
    static int t = 0, s[10];

    do
    {
        s[t] = x % 10;
        x /= 10;
        ++t;
    } while (x != 0);

    while (t > 0)
    {
        --t;
        putchar(s[t] + 48);
    }
    putchar('\n');
}

const int maxn = 1e5, mod = 1e9 + 7;

int n, f[maxn + 1], dfc, dfn[maxn + 1], rnk[maxn + 1], siz[maxn + 1], sum[maxn + 1], ans[maxn];
std::vector<int> g[maxn + 1];
std::vector<std::pair<int, int>> q[maxn + 1];

class BIT
{
private:
    int t[maxn + 1];

    int lowbit(int x) { return x & -x; }

public:
    void build() { std::fill_n(t + 1, n, 0); }

    void modify(int x, int v)
    {
        for (int i = x; i <= n; i += lowbit(i))
            t[i] = (t[i] + v) % mod;
    }

    int query(int x)
    {
        int ret = 0;
        for (int i = x; i > 0; i -= lowbit(i))
            ret = (ret + t[i]) % mod;
        return ret;
    }
} s;

void dp(int x, int fa)
{
    f[x] = g[x].size();
    ++dfc;
    dfn[x] = dfc;
    rnk[dfc] = x;
    siz[x] = 1;

    for (int v : g[x])
        if (v != fa)
        {
            dp(v, x);
            f[x] = (f[x] + f[v]) % mod;
            siz[x] += siz[v];
        }
}

void stat(int x, int fa)
{
    for (int v : g[x])
        if (v != fa)
        {
            sum[v] = (sum[x] + f[v]) % mod;
            stat(v, x);
        }
}

void solve(int x, int fa)
{
    int ffa = f[fa], fx = f[x];
    if (x != 1)
    {
        f[fa] = (f[fa] - f[x]) % mod;
        f[x] = ffa;
        s.modify(1, (ffa - fx) % mod);
        s.modify(dfn[x], -ffa);
        s.modify(dfn[x] + siz[x], ffa);
    }

    for (std::pair<int, int> pr : q[x])
        ans[pr.second] = s.query(dfn[pr.first]);

    for (int v : g[x])
        if (v != fa)
            solve(v, x);

    if (x != 1)
    {
        f[fa] = ffa;
        f[x] = fx;
        s.modify(1, (fx - ffa) % mod);
        s.modify(dfn[x], ffa);
        s.modify(dfn[x] + siz[x], -ffa);
    }
}

int main()
{
    std::freopen("tree.in", "r", stdin);
    std::freopen("tree.out", "w", stdout);

    int m;
    read(n);
    read(m);

    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u);
        read(v);
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }

    for (int i = 0; i < m; ++i)
    {
        int s, t;
        read(s);
        read(t);
        q[t].emplace_back(s, i);
    }

    dp(1, 1);
    stat(1, 1);

    s.build();
    for (int i = 1; i <= n; ++i)
        s.modify(i, (sum[rnk[i]] - sum[rnk[i - 1]]) % mod);

    solve(1, 1);

    for (int i = 0; i < m; ++i)
        write((ans[i] + mod) % mod);
    return 0;
}