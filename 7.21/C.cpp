#include <bits/stdc++.h>

const int mod = 1e9 + 7;

int n, *fac, *inv;

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

void init()
{
    fac = new int[n + 1];
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = 1ll * fac[i - 1] * i % mod;
    inv = new int[n + 1];
    inv[n] = getinv(fac[n]);
    for (int i = n; i > 0; --i)
        inv[i - 1] = 1ll * inv[i] * i % mod;
}

int C(int n, int m) { return 1ll * fac[n] * inv[n - m] % mod * inv[m] % mod; }

int Catalan(int n) { return 1ll * C(n * 2, n) * getinv(n + 1) % mod; }

int solve0(int n)
{
    int ans = 0;
    for (int i = 0; i * 2 <= n; ++i)
        ans = (ans + 1ll * C(n, i) * C(n - i, i) % mod * C(n - i * 2, n / 2 - i) % mod) % mod;
    return ans;
}

int solve1(int n) { return Catalan(n / 2); }

int solve2(int n)
{
    int *f = new int[n / 2 + 1]();
    f[0] = 1;
    for (int i = 1; i <= n / 2; ++i)
        for (int j = 1; j <= i; ++j)
            f[i] = (f[i] + 1ll * f[i - j] * C(j * 2, j) % mod) % mod;
    return 2ll * f[n / 2] % mod;
}

int solve3(int n)
{
    int sum = 0;
    for (int i = 0; i <= n; i += 2)
        sum = (sum + 1ll * C(n, i) * Catalan(i / 2) % mod * Catalan((n - i) / 2) % mod) % mod;
    return sum;
}

int main()
{
    freopen("C.in", "r", stdin);
    int type;
    std::cin >> n >> type;
    init();
    switch (type)
    {
    case 0:
        std::cout << solve0(n) << std::endl;
        break;
    case 1:
        std::cout << solve1(n) << std::endl;
        break;
    case 2:
        std::cout << solve2(n) << std::endl;
        break;
    case 3:
        std::cout << solve3(n) << std::endl;
        break;
    }
    return 0;
}