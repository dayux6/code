#include <bits/stdc++.h>

const int maxm = 100;

struct edge
{
    int u, v, w;
} e[maxm];

struct matrix
{
    int n, a[maxm * 2 + 1][maxm * 2 + 1];

    matrix(int _n) : n(_n)
    {
        for (int i = 1; i <= _n; ++i)
            std::fill_n(a[i] + 1, _n, INT_MAX);
    }

    matrix operator*(matrix rhs)
    {
        matrix ret(n);
        for (int i = 1; i <= n; ++i)
            for (int k = 1; k <= n; ++k)
                if (a[i][k] != INT_MAX)
                    for (int j = 1; j <= n; ++j)
                        if (rhs.a[k][j] != INT_MAX)
                            ret.a[i][j] = std::min(ret.a[i][j], a[i][k] + rhs.a[k][j]);
        return ret;
    }
};

matrix qpow(matrix x, int n)
{
    matrix ret = x;
    --n;
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
    freopen("F.in", "r", stdin);
    int k, m, s, t;
    std::cin >> k >> m >> s >> t;

    std::vector<int> v;
    for (int i = 0; i < m; ++i)
    {
        std::cin >> e[i].w >> e[i].u >> e[i].v;
        v.push_back(e[i].u);
        v.push_back(e[i].v);
    }

    std::sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()), v.end());
    matrix base(v.size());
    for (int i = 0; i < m; ++i)
    {
        int x = std::lower_bound(v.begin(), v.end(), e[i].u) - v.begin() + 1, y = std::lower_bound(v.begin(), v.end(), e[i].v) - v.begin() + 1;
        base.a[x][y] = base.a[y][x] = e[i].w;
    }
    std::cout << qpow(base, k).a[std::lower_bound(v.begin(), v.end(), s) - v.begin() + 1][std::lower_bound(v.begin(), v.end(), t) - v.begin() + 1] << std::endl;
    return 0;
}