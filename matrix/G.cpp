#include <bits/stdc++.h>

const int maxn = 3e2;

struct matrix
{
    int n, a[maxn + 1][maxn + 1];

    matrix(int _n) : n(_n)
    {
        for (int i = 1; i <= _n; ++i)
        {
            std::fill_n(a[i] + 1, _n, INT_MAX);
            a[i][i] = 0;
        }
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
    matrix ret(x.n);
    ret = x;
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
    freopen("G.in", "r", stdin);
    int n, m;
    std::cin >> n >> m;

    matrix x(n);
    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        x.a[u][v] = w;
    }

    auto check = [=](int k)
    {
        matrix res = qpow(x, k);
        for (int i = 1; i <= n; ++i)
            if (res.a[i][i] < 0)
                return true;
        return false;
    };

    int l = 1, r = n, ans = 0;
    while (l <= r)
    {
        int mid = (l + r) / 2;

        if (check(mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    std::cout << ans << std::endl;
    return 0;
}