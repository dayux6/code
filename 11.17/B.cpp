#include <bits/stdc++.h>

long long p;

struct matrix
{
    long long a[2][2];

    matrix() { std::memset(a, 0, sizeof(a)); }

    matrix operator*(matrix rhs)
    {
        matrix ret;

        for (long long k = 0; k < 2; ++k)
            for (long long i = 0; i < 2; ++i)
                for (long long j = 0; j < 2; ++j)
                    ret.a[i][j] = (ret.a[i][j] + a[i][k] * rhs.a[k][j] % p) % p;

        return ret;
    }
};

matrix qpow(matrix x, long long n)
{
    matrix ret;
    ret.a[0][0] = ret.a[1][1] = 1;

    while (n != 0)
    {
        if (n & 1)
            ret = ret * x;
        x = x * x;
        n >>= 1;
    }

    return ret;
}

void exgcd(long long a, long long b, long long &x, long long &y)
{
    if (a == 0)
    {
        x = 0;
        y = 1;
    }
    else
    {
        exgcd(b % a, a, y, x);
        x -= (b / a) * y;
    }
}

int main()
{
    std::freopen("fib.in", "r", stdin);
    std::freopen("fib.out", "w", stdout);

    long long t;
    std::cin >> t;

    matrix fib;
    fib.a[0][1] = fib.a[1][0] = fib.a[1][1] = 1;
    for (long long _ = 0, i, l, r, k, m; _ < t; ++_)
    {
        std::cin >> i >> l >> r >> k >> p >> m;
        i %= p;

        matrix mat = qpow(fib, k - 2);
        m = ((m - i * mat.a[0][1] % p) % p + p) % p;
        long long g = std::__gcd(mat.a[1][1], p);
        if (m % g != 0)
            std::cout << 0 << '\n';
        else
        {
            mat.a[1][1] /= g;
            p /= g;
            m /= g;
            long long j, k;
            exgcd(mat.a[1][1], p, j, k);
            j *= m;
            j -= std::floor(1.0 * (j - l) / p) * p;
            if (j > r)
                std::cout << 0 << '\n';
            else
                std::cout << (r - j) / p + 1 << '\n';
        }
    }
    return 0;
}