#include <bits/stdc++.h>

const int maxn = 30;

int mod;

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

    matrix operator*(matrix rhs)
    {
        matrix ret(n);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
            {
                ret.a[i][j] = 0;
                for (int k = 1; k <= n; ++k)
                    ret.a[i][j] = (ret.a[i][j] + 1ll * a[i][k] * rhs.a[k][j] % mod) % mod;
            }
        return ret;
    }
} base;

std::pair<matrix, matrix> calc(int k)
{
    if (k == 1)
        return std::make_pair(base, base);
    else
    {
        std::pair<matrix, matrix> pr = calc(k / 2), ret;
        ret.first = pr.first * pr.first;
        ret.second = pr.second + pr.second * pr.first;
        if (k & 1)
        {
            ret.first = ret.first * base;
            ret.second = ret.second + ret.first;
        }
        return ret;
    }
}

int main()
{
    freopen("D.in", "r", stdin);
    int k;
    std::cin >> base.n >> k >> mod;
    for (int i = 1; i <= base.n; ++i)
        for (int j = 1; j <= base.n; ++j)
            std::cin >> base.a[i][j];

    matrix res = calc(k).second;
    for (int i = 1; i <= base.n; ++i)
    {
        for (int j = 1; j <= base.n; ++j)
            std::cout << res.a[i][j] << ' ';
        std::cout << std::endl;
    }
    return 0;
}