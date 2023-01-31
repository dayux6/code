#include <bits/stdc++.h>

const int maxn = 400;

int fac[maxn + 1], inv[maxn + 1], f[maxn + 1][maxn + 1], s[maxn + 1][maxn + 1];

int qpow(int x, int n, const int mod)
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

int main()
{
    freopen("A.in", "r", stdin);
    int n, p;
    std::cin >> n >> p;

    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = 1ll * fac[i - 1] * i % p;
    inv[n] = qpow(fac[n], p - 2, p);
    for (int i = n; i; --i)
        inv[i - 1] = 1ll * inv[i] * i % p;

    auto C = [=](int n, int m)
    { return 1ll * fac[n] * inv[n - m] % p * inv[m] % p; };

    f[1][1] = 1;
    for (int i = 1; i <= n; ++i)
        s[1][i] = 1;
    for (int i = 2; i <= n; ++i)
    {
        for (int j = 2; j <= i; ++j)
        {
            for (int k = 1; k < i; ++k)
                f[i][j] = ((f[i][j] + C(i - 2, k - 1) * (1ll * f[k][j] * s[i - k][j - 2] % p + 1ll * f[k][j - 1] * s[i - k][j] % p) % p) % p) % p;
            s[i][j] = (s[i][j - 1] + f[i][j]) % p;
        }
        for (int j = i + 1; j <= n; ++j)
            s[i][j] = s[i][i];
    }

    int sum = 0, ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        sum = (sum + f[n][i]) % p;
        ans = (ans + 1ll * i * f[n][i] % p) % p;
    }
    std::cout << 1ll * ans * qpow(sum, p - 2, p) % p << std::endl;
    return 0;
}