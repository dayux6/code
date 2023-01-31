#include <bits/stdc++.h>

const int mod = 1e6 + 3;

int qpow(int x, long long n = mod - 2)
{
    int ret = 1;

    n %= mod - 1;
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
    std::freopen("random.in", "r", stdin);
    std::freopen("random.out", "w", stdout);

    long long n, m;
    std::cin >> n >> m;

    if (std::log2(m) > n)
    {
        std::cout << "1 1" << std::endl;
        return 0;
    }

    long long cnt = n;
    for (long long i = 2; i < m; i *= 2)
        cnt += (m - 1) / i;

    int pw = qpow(2, n), tmp = 1ll * qpow(qpow(2, n), m) * qpow(qpow(2, cnt)) % mod;
    if (m > pw)
        std::cout << tmp << ' ' << tmp << std::endl;
    else
    {
        int ans = 1;
        for (int i = 0; i < m; ++i)
            ans = 1ll * ans * (pw - i) % mod;
        ans = 1ll * ans * qpow(qpow(2, cnt)) % mod;
        std::cout << ((tmp - ans) % mod + mod) % mod << ' ' << tmp << std::endl;
    }
    return 0;
}