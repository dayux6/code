#include <bits/stdc++.h>

const int maxn = 30, mod = 1e4 + 7;

struct matrix
{
    int n, a[maxn + 1][maxn + 1];

    matrix(int _n) : n(_n)
    {
        for (int i = 1; i <= n; ++i)
            std::fill_n(a[i] + 1, _n, 0);
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
};

matrix qpow(matrix x, int n)
{
    matrix ret(x.n);
    for (int i = 1; i <= ret.n; ++i)
        ret.a[i][i] = 1;
    while (n != 0)
    {
        if (n & 1)
            ret = ret * x;
        x = x * x;
        n >>= 1;
    }
    return ret;
}

int main()
{
    freopen("E.in", "r", stdin);
    int n, s, t, k;
    std::cin >> n >> s >> t >> k;

    matrix base(n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            std::cin >> base.a[i][j];
    std::cout << qpow(base, k).a[s][t] << std::endl;
    return 0;
}