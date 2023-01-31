#include <bits/stdc++.h>

const int maxn = 5e5, mod = 998244353;

int n, m, fac[maxn * 2 + 1], ifac[maxn * 2 + 1];

int qpow(int x, int n = mod - 2)
{
    int ret = 1;

    while (n)
    {
        if (n & 1)
            ret = 1ll * ret * x % mod;
        x = 1ll * x * x % mod;
        n >>= 1;
    }

    return ret;
}

void init()
{
    fac[0] = 1;
    for (int i = 1; i <= n + m; ++i)
        fac[i] = 1ll * fac[i - 1] * i % mod;
    ifac[n + m] = qpow(fac[n + m]);
    for (int i = n + m; i > 0; --i)
        ifac[i - 1] = 1ll * ifac[i] * i % mod;
}

int C(int n, int m) { return 1ll * fac[n] * ifac[n - m] % mod * ifac[m] % mod; }

int calc(int n, int m) { return C(n + m, n); }

int main()
{
    std::freopen("AGC019F.in", "r", stdin);

    std::cin >> n >> m;
    if (n < m)
        std::swap(n, m);

    init();

    int sum = 0;
    for (int i = 1; i <= m; ++i)
        sum = (sum + 1ll * calc(n - i, m - i) * calc(i, i) % mod) % mod;

    std::cout << (n + 1ll * qpow(2) * sum % mod * qpow(calc(n, m)) % mod) % mod << std::endl;
    return 0;
}