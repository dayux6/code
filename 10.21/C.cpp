#include <bits/stdc++.h>

const int mod = 998244353, maxm = 100, maxlg = 29;

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

int f[maxm * 2 + 1][maxm * maxlg + 1];

int main()
{
    std::freopen("count.in", "r", stdin);
    std::freopen("count.out", "w", stdout);

    int n, m;
    std::cin >> n >> m;

    int cnt = 0;
    for (int i = 1; i * i <= n; ++i)
        if (n % i == 0)
        {
            ++cnt;
            if (i != n / i)
                ++cnt;
        }

    int x = n, ans = 1;
    for (int i = 2; i * i <= x; ++i)
        if (x % i == 0)
        {
            int c = 0;
            while (x % i == 0)
            {
                x /= i;
                ++c;
            }

            f[0][0] = 1;
            for (int j = 1; j <= m * 2; ++j)
            {
                std::fill_n(f[j], m * c + 1, 0);

                for (int k = 0; k <= j * c; ++k)
                    for (int l = 0; l <= c && l <= k; ++l)
                        f[j][k] = (f[j][k] + f[j - 1][k - l]) % mod;
            }

            ans = 1ll * ans * f[m * 2][m * c] % mod;
        }

    if (x != 1)
    {
        f[0][0] = 1;
        for (int j = 1; j <= m * 2; ++j)
        {
            std::fill_n(f[j], m + 1, 0);

            for (int k = 0; k <= j; ++k)
                for (int l = 0; l <= 1 && l <= k; ++l)
                    f[j][k] = (f[j][k] + f[j - 1][k - l]) % mod;
        }

        ans = 1ll * ans * f[m * 2][m] % mod;
    }

    std::cout << ((1ll * (qpow(cnt, m * 2) - ans) * qpow(2) % mod + ans) % mod + mod) % mod << std::endl;
    return 0;
}