#include <bits/stdc++.h>

const int maxn = 10, maxw = 10, mod = 2009;

char e[maxn][maxn];

struct matrix
{
    int n, a[maxn + maxn * (maxn - 1) * (maxw - 1)][maxn + maxn * (maxn - 1) * (maxw - 1)];

    matrix(int _n) : n(_n)
    {
        for (int i = 0; i < _n; ++i)
            for (int j = 0; j < _n; ++j)
                a[i][j] = 0;
    }

    matrix operator*(matrix rhs)
    {
        matrix ret(n);
        for (int i = 0; i < n; ++i)
            for (int k = 0; k < n; ++k)
                for (int j = 0; j < n; ++j)
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
    freopen("H.in", "r", stdin);
    int n, k;
    std::cin >> n >> k;

    int sum = n;
    for (int i = 0; i < n; ++i)
    {
        scanf("%s", e[i]);
        for (int j = 0; j < n; ++j)
            if (e[i][j] != '0')
                sum += e[i][j] - '0' - 1;
    }

    matrix x(sum);
    int cnt = n;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (e[i][j] != '0')
            {
                int pre = i;
                for (int k = 0; k < e[i][j] - '0' - 1; ++k)
                {
                    x.a[pre][cnt] = 1;
                    pre = cnt;
                    ++cnt;
                }
                x.a[pre][j] = 1;
            }
    std::cout << qpow(x, k).a[0][n - 1] << std::endl;
    return 0;
}