#include <bits/stdc++.h>

const int mod = 1e9 + 7;

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

int main()
{
    freopen("B.in", "r", stdin);
    int n, m, k;
    std::cin >> n >> m >> k;
    int ans = 0;
    for (int i = 1; i <= m; ++i)
    {
        int wt;
        std::cin >> wt;
        ans = (ans + 1ll * (qpow(i, k) - qpow(i - 1, k)) % mod * wt % mod) % mod;
    }
    std::cout << (1ll * (n - k + 1) * qpow(m, n - k) % mod * ans % mod * getinv(qpow(m, n)) % mod + mod) % mod << std::endl;
    return 0;
}