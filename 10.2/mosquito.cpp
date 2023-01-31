#include <bits/stdc++.h>

const int mod = 1e9 + 7, maxn = 1e6;

void read(int &x)
{
    x = 0;
    char c = getchar();

    while (!isdigit(c))
        c = getchar();

    while (isdigit(c))
    {
        x = x * 10 + (c ^ 48);
        c = getchar();
    }
}

int qpow(int x, int n = mod - 2)
{
    int ret = 1;

    while (n != 0)
    {
        if (n & 1)
            ret = 1ll * ret * x % mod;
        x = 1ll * x * x % mod;
        n >>= 1;
    }
    return ret;
}

int d, p, cnt, ans, f[maxn + 1], dep[maxn + 1];
std::vector<int> g[maxn + 1];

void dfs(int x, int fa)
{
    for (int v : g[x])
        if (v != fa)
        {
            dep[v] = dep[x] + 1;
            dfs(v, x);
        }

    if (g[x].size() == 1)
    {
        f[x] = dep[x] <= d ? p : 1;
        ++cnt;
    }
    else
        for (int v : g[x])
            if (v != fa)
            {
                ans = (ans + 2ll * f[x] * f[v] % mod) % mod;
                f[x] = (f[x] + (dep[x] <= d ? 1ll * p * f[v] % mod : f[v])) % mod;
            }
}

int main()
{
    freopen("mosquito.in", "r", stdin);
    freopen("mosquito.out", "w", stdout);

    int n;
    read(n);

    for (int i = 1; i < n; ++i)
    {
        int u, v;
        read(u);
        read(v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int q;
    read(d);
    read(p);
    read(q);
    p = 1 - 1ll * p * qpow(q) % mod;

    dfs(1, 0);

    std::cout << ((1ll * cnt * (cnt - 1) % mod - ans) % mod + mod) % mod << std::endl;
    return 0;
}