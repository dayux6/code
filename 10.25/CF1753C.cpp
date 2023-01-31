#include <bits/stdc++.h>

const int maxn = 2e5, mod = 998244353;

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

std::array<bool, maxn + 1> a;

int solve()
{
    int n;
    std::cin >> n;

    int cnt1 = 0;
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> a[i];
        cnt1 += a[i];
    }

    int cur = 0;
    for (int i = 0; i < cnt1; ++i)
        cur += a[n - i];

    int ret = 0;
    for (int i = cur; i < cnt1; ++i)
        ret = (ret + qpow(2ll * qpow(cnt1 - i, 2) % mod * qpow(1ll * n * (n - 1) % mod) % mod)) % mod;

    return ret;
}

int main()
{
    std::freopen("CF1753C.in", "r", stdin);

    int t;
    std::cin >> t;

    for (int i = 0; i < t; ++i)
        std::cout << solve() << std::endl;
    return 0;
}