#include <bits/stdc++.h>

const int maxn = 2e5, mod = 998244353;

int qpow(int x, int n)
{
    int ret = 1;
    while (n)
    {
        if (n & 1)
            ret = 1ll * ret * x % mod;
        x = 1ll * x * x % mod;
        n /= 2;
    }
    return ret;
}

int getinv(int x) { return qpow(x, mod - 2); }

int a[maxn + 1], f[maxn + 1], s[maxn + 2];

int main()
{
    int n;
    std::cin >> n;

    for (int i = 1; i < n; ++i)
        std::cin >> a[i];

    for (int i = n - 1; i >= 1; --i)
    {
        f[i] = (1ll * (s[i + 1] - s[i + a[i] + 1] + 1) * getinv(a[i]) % mod + 1) % mod;
        s[i] = (s[i + 1] + f[i]) % mod;
    }

    std::cout << (f[1] + mod) % mod << std::endl;
    return 0;
}