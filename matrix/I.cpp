#include <bits/stdc++.h>

const int maxn = 100, mod = 1e9 + 7;

struct matrix
{
    int n, a[maxn + 1][maxn + 1];

    matrix() {}
    matrix(int _n) : n(_n)
    {
        for (int i = 1; i <= _n; ++i)
            std::fill_n(a[i] + 1, _n, 0);
    }

    matrix operator+(matrix rhs)
    {
        matrix ret(n);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                ret.a[i][j] = (a[i][j] + rhs.a[i][j]) % mod;
        return ret;
    }

    matrix operator*(int k)
    {
        matrix ret(n);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                ret.a[i][j] = 1ll * a[i][j] * k % mod;
        return ret;
    }

    matrix operator*(matrix rhs)
    {
        matrix ret(n);
        for (int i = 1; i <= n; ++i)
            for (int k = 1; k <= n; ++k)
                for (int j = 1; j <= n; ++j)
                    ret.a[i][j] = (ret.a[i][j] + 1ll * a[i][k] * rhs.a[k][j] % mod) % mod;
        return ret;
    }
} g, a, b, c, d;

void solve(int k)
{
    if (k == 1)
    {
        a = b = c = d = g;
        return;
    }
    else
    {
        int m = k / 2;
        solve(m);

        matrix tmpb = b * a, tmpc = c * a;
        d = d + d * a + tmpc * (m * 2) + tmpb * (1ll * m * m % mod);
        c = c + tmpc + tmpb * m;
        b = b + tmpb;
        a = a * a;

        if (k & 1)
        {
            a = a * g;
            b = b + a;
            c = c + a * k;
            d = d + a * (1ll * k * k % mod);
        }
    }
}

int main()
{
    freopen("I.in", "r", stdin);
    int m, k, q;
    std::cin >> g.n >> m >> k >> q;

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        std::cin >> u >> v;
        ++g.a[u][v];
    }

    solve(k);

    for (int i = 0; i < q; ++i)
    {
        int s, t;
        std::cin >> s >> t;
        std::cout << d.a[s][t] << std::endl;
    }
    return 0;
}