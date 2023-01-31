#include <bits/stdc++.h>

const int mod = 1e9 + 7;

struct matrix
{
    int a[3][3];

    matrix operator*(matrix rhs)
    {
        matrix ret;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
            {
                ret.a[i][j] = 0;
                for (int k = 0; k < 3; ++k)
                    ret.a[i][j] = (ret.a[i][j] + 1ll * a[i][k] * rhs.a[k][j] % mod) % mod;
            }
        return ret;
    }
};

matrix qpow(matrix x, int n)
{
    matrix ret;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            ret.a[i][j] = i == j;
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
    freopen("C.in", "r", stdin);
    matrix base;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            base.a[i][j] = 0;
    base.a[1][0] = base.a[2][1] = base.a[0][2] = base.a[2][2] = 1;

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
    {
        int n;
        std::cin >> n;
        if (n <= 3)
            std::cout << 1 << std::endl;
        else
        {
            matrix res = qpow(base, n - 3);
            std::cout << ((res.a[0][2] + res.a[1][2]) % mod + res.a[2][2]) % mod << std::endl;
        }
    }
    return 0;
}