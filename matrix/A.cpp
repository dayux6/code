#include <bits/stdc++.h>

const int maxn = 200;

struct matrix
{
    int n, m, a[maxn + 1][maxn + 1];

    matrix(int _n, int _m) : n(_n), m(_m)
    {
        for (int i = 1; i <= _n; ++i)
            std::fill_n(a[i] + 1, _m, 0);
    }

    matrix()
    {
        std::cin >> n >> m;

        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                std::cin >> a[i][j];
    }

    matrix operator*(matrix rhs)
    {
        matrix ret(n, rhs.m);
        for (int k = 1; k <= m; ++k)
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= rhs.m; ++j)
                    ret.a[i][j] += a[i][k] * rhs.a[k][j];
        return ret;
    }

    void print()
    {
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
                std::cout << a[i][j] << ' ';
            std::cout << std::endl;
        }
    }
};

int main()
{
    freopen("A.in", "r", stdin);
    matrix a, b;
    (a * b).print();
    return 0;
}