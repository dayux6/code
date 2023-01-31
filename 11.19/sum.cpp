#include <bits/stdc++.h>

const int maxn = 50, mod = 1e9 + 7;

int a[maxn + 1], p[maxn + 1];

int qpow(int x, int n = mod - 2)
{
    int ret = 1;

    while (n != 0)
    {
        if (n & 1)
            ret = 1ll * ret * x % mod;
        x = 1ll * x * x % mod;
        n >>= 1;
    }

    return ret;
}

int main()
{
    std::freopen("sum.in", "r", stdin);
    std::freopen("sum.out", "w", stdout);

    int n;
    std::cin >> n;

    int sum = 0;
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> a[i];
        sum = (sum + a[i]) % mod;
    }

    int fac = 1;
    for (int i = 2; i <= sum; ++i)
        fac = 1ll * fac * i % mod;

    std::iota(p + 1, p + n + 1, 1);
    int res = 0;
    do
    {
        int pro = 1, s = a[p[1]];
        for (int i = 2; i <= n; ++i)
        {
            s += a[p[i]];
            pro = 1ll * pro * s % mod;
        }
        res = (res + qpow(pro)) % mod;
    } while (std::next_permutation(p + 1, p + n + 1));

    std::cout << 1ll * fac * res % mod << std::endl;
    return 0;
}