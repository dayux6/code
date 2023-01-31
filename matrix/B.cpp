#include <bits/stdc++.h>

const int mod = 1e9 + 7;

struct matrix
{
    int a[2][2];

    matrix operator*(matrix rhs)
    {
        matrix ret;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
            {
                ret.a[i][j] = 0;
                for (int k = 0; k < 2; ++k)
                    ret.a[i][j] = (ret.a[i][j] + 1ll * a[i][k] * rhs.a[k][j] % mod) % mod;
            }
        return ret;
    }
};

matrix qpow(matrix x, long long n)
{
    matrix ret;
    ret.a[0][0] = ret.a[1][1] = 1;
    ret.a[0][1] = ret.a[1][0] = 0;
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
    freopen("B.in", "r", stdin);
    matrix base;
    base.a[0][0] = 0;
    base.a[0][1] = base.a[1][0] = base.a[1][1] = 1;
    long long n;
    std::cin >> n;
    std::cout << qpow(base, n - 1).a[1][1] << std::endl;
    return 0;
}