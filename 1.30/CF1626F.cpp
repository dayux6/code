#include <bits/stdc++.h>

const int maxk = 17, mod = 998244353;

int pw[maxk], f[maxk + 1][720720];

int main()
{
    std::freopen("CF1626F.in", "r", stdin);

    int n, a0, x, y, k, M;
    std::cin >> n >> a0 >> x >> y >> k >> M;

    int lcm = 1;
    for (int i = 2; i < k; ++i)
        lcm = lcm / std::__gcd(lcm, i) * i;

    ++f[1][a0 % lcm];
    int cnt = a0 / lcm;
    for (int i = 1; i < n; ++i)
    {
        a0 = (1ll * a0 * x + y) % M;

        ++f[1][a0 % lcm];
        cnt = (cnt + a0 / lcm) % mod;
    }

    pw[0] = 1;
    for (int i = 1; i < k; ++i)
        pw[i] = 1ll * pw[i - 1] * n % mod;
    int ans = 1ll * cnt * k % mod * lcm % mod * pw[k - 1] % mod;
    for (int i = 1; i < k; ++i)
    {
        for (int j = 0; j < lcm; ++j)
            if (f[i][j] != 0)
            {
                f[i + 1][j] = (f[i + 1][j] + 1ll * (n - 1) * f[i][j] % mod) % mod;
                f[i + 1][j - (j % i)] = (f[i + 1][j - (j % i)] + f[i][j]) % mod;

                ans = (ans + 1ll * j * f[i][j] % mod * pw[k - i] % mod) % mod;
            }
    }
    for (int i = 0; i < lcm; ++i)
        ans = (ans + 1ll * i * f[k][i] % mod) % mod;

    std::cout << ans << std::endl;
    return 0;
}