#include <bits/stdc++.h>

const int maxn = 1e5, maxk = 2e3, maxlg = 21, mod = 1e9 + 7;

int fac[maxn * 2 + 1], ifac[maxn * 2 + 1], f[maxk + 2][maxlg + 1];
std::pair<int, int> pr[maxk + 1];

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

void init(int n)
{
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = 1ll * fac[i - 1] * i % mod;

    ifac[n] = qpow(fac[n]);
    for (int i = n; i > 0; --i)
        ifac[i - 1] = 1ll * ifac[i] * i % mod;
}

int C(int n, int m) { return 1ll * fac[n] * ifac[n - m] % mod * ifac[m] % mod; }

int calc(int n, int m) { return C(n + m, n); }

int main()
{
    std::freopen("CF722E.in", "r", stdin);

    int n, m, k, s;
    std::cin >> n >> m >> k >> s;

    for (int i = 1; i <= k; ++i)
        std::cin >> pr[i].first >> pr[i].second;
    std::sort(pr + 1, pr + k + 1);

    pr[0].first = pr[0].second = 1;
    ++k;
    pr[k].first = n;
    pr[k].second = m;

    init(n + m);
    f[0][0] = 1;
    for (int i = 1; i <= k; ++i)
    {
        for (int j = 0; j < i; ++j)
            if (pr[j].first <= pr[i].first && pr[j].second <= pr[i].second)
                for (int c = 0; c <= maxlg; ++c)
                    f[i][c] = (f[i][c] + 1ll * f[j][std::max(0, c - 1)] * calc(pr[i].first - pr[j].first, pr[i].second - pr[j].second) % mod) % mod;

        for (int j = 0; j < maxlg; ++j)
            f[i][j] = (f[i][j] - f[i][j + 1]) % mod;
    }

    int ans = 0;
    for (int i = 1; i <= maxlg; ++i)
    {
        ans = (ans + 1ll * f[k][i] * s % mod) % mod;
        s = std::ceil(s / 2.0);
    }

    std::cout << (1ll * ans * qpow(calc(n - 1, m - 1)) % mod + mod) % mod << std::endl;
    return 0;
}