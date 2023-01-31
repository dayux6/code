#include <bits/stdc++.h>

const int maxn = 400, mod = 998244353;

int n, lim, dis[maxn + 1][maxn + 1], fa[maxn + 1], siz[maxn + 1], fac[maxn + 1], inv[maxn + 1], f[maxn + 1], g[maxn + 1];

int qpow(int x, int n)
{
    int ret = 1;
    while (n)
    {
        if (n & 1)
            ret = 1ll * ret * x % mod;
        x = 1ll * x * x % mod;
        n /= 2;
    }
    return ret;
}

int getinv(int x) { return qpow(x, mod - 2); }

int find(int x)
{
    while (x != fa[x])
        x = fa[x] = fa[fa[x]];
    return x;
}

void merge(int x, int y)
{
    x = find(x);
    y = find(y);
    if (x ^ y)
    {
        fa[y] = x;
        siz[x] += siz[y];
    }
}

int main()
{
    freopen("C.in", "r", stdin);
    std::cin >> n >> lim;

    std::iota(fa + 1, fa + n + 1, 1);
    std::fill_n(siz + 1, n, 1);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            std::cin >> dis[i][j];
            if (dis[i][j] == 0)
                merge(i, j);
        }
        if (dis[i][i])
        {
            std::cout << 0 << std::endl;
            return 0;
        }
    }

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (dis[i][j] ^ dis[j][i] || dis[i][j] > lim)
            {
                std::cout << 0 << std::endl;
                return 0;
            }

    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (dis[i][j] > dis[i][k] + dis[k][j])
                {
                    std::cout << 0 << std::endl;
                    return 0;
                }

    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = 1ll * fac[i - 1] * i % mod;
    inv[n] = getinv(fac[n]);
    for (int i = n; i >= 1; --i)
        inv[i - 1] = 1ll * inv[i] * i % mod;
    auto C = [=](int n, int m)
    { return 1ll * fac[n] * inv[n - m] % mod * inv[m] % mod; };

    for (int i = 1; i <= n; ++i)
    {
        g[i] = qpow(lim + 1, i * (i - 1) / 2);
        f[i] = g[i];
        for (int j = 1; j < i; ++j)
            f[i] = (f[i] - 1ll * f[j] * g[i - j] % mod * C(i - 1, j - 1) % mod * qpow(lim, j * (i - j)) % mod) % mod;
    }

    int ans = 1;
    for (int i = 1; i <= n; ++i)
        if (i == find(i))
        {
            ans = 1ll * ans * f[siz[i]] % mod;
            for (int j = 1; j < i; ++j)
                if (j == find(j))
                {
                    bool b = true;
                    for (int k = 1; k <= n; ++k)
                        if (i ^ k && j ^ k && k == find(k) && dis[i][j] == dis[i][k] + dis[k][j])
                        {
                            b = false;
                            break;
                        }

                    if (b)
                        ans = 1ll * ans * (qpow(lim - dis[i][j] + 1, siz[i] * siz[j]) - qpow(lim - dis[i][j], siz[i] * siz[j])) % mod;
                    else
                        ans = 1ll * ans * qpow(lim - dis[i][j] + 1, siz[i] * siz[j]) % mod;
                }
        }

    std::cout << (ans + mod) % mod << std::endl;
    return 0;
}