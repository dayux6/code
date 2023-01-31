#include <bits/stdc++.h>

const int maxn = 30, mod = 1e9 + 7;

int n;

struct matrix
{
    int a[maxn][maxn];

    matrix()
    {
        for (int i = 0; i < n; ++i)
            std::fill_n(a[i], n, 0);
    }

    matrix operator*(matrix rhs)
    {
        matrix ret;

        for (int k = 0; k < n; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    ret.a[i][j] = (ret.a[i][j] + 1ll * a[i][k] * rhs.a[k][j] % mod) % mod;

        return ret;
    }
};

matrix qpow(matrix x, int n)
{
    if (n == 0)
        return matrix();
    else
    {
        matrix ret = x;
        --n;

        while (n)
        {
            if (n & 1)
                ret = ret * x;
            x = x * x;
            n >>= 1;
        }

        return ret;
    }
}

int main()
{
    std::freopen("walk.in", "r", stdin);
    std::freopen("walk.out", "w", stdout);

    int m, l;
    std::string str;
    std::cin >> n >> m >> l >> str;

    std::vector<int> vct;
    for (int i = 0; i < n; ++i)
        if (str[i] == '1')
            vct.emplace_back(i);

    matrix base;
    for (int i = 0, u, v; i < m; ++i)
    {
        std::cin >> u >> v;
        ++base.a[u][v];
    }

    int ans = 0;
    matrix tmp;
    for (int i = 0; i < (1 << vct.size()); ++i)
    {
        tmp = base;
        for (std::size_t j = 0; j < vct.size(); ++j)
            if ((i >> j) & 1)
                for (int k = 0; k < n; ++k)
                    tmp.a[vct[j]][k] = tmp.a[k][vct[j]] = 0;

        tmp = qpow(tmp, l);

        int v = __builtin_popcount(i) & 1 ? -1 : 1;
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                ans = (ans + v * tmp.a[j][k]) % mod;
    }

    std::cout << (ans + mod) % mod << std::endl;
    return 0;
}