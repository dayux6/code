/*
分块大法好
莫笑分块没头脑，要说好处真不少。
又好写来又好调，代码简单常数小。
对数算法真难找，考虑根号没烦恼。
管它点分线段树，直接分块就没了！
                        ---ycx
*/

#include <bits/stdc++.h>

const int maxn = 1e5, bsiz = 4e2, bcnt = 2.5e2, mod = 1e9 + 7;

int fac[maxn + 1], inv[maxn + 1], sum[maxn + 1][bcnt];

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
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    fac[0] = 1;
    for (int i = 1; i <= maxn; ++i)
        fac[i] = 1ll * fac[i - 1] * i % mod;
    inv[maxn] = getinv(fac[maxn]);
    for (int i = maxn; i >= 1; --i)
        inv[i - 1] = 1ll * inv[i] * i % mod;
    auto C = [=](int n, int m)
    {
        if (n < m || m < 0)
            return 0ll;
        else
            return 1ll * fac[n] * inv[n - m] % mod * inv[m] % mod;
    };
    sum[0][0] = 1;
    for (int i = 1; i <= maxn; ++i)
        for (int j = 0; j < bcnt; ++j)
            sum[i][j] = ((2ll * sum[i - 1][j] % mod + C(i - 1, j * bsiz - 1)) % mod - C(i - 1, (j + 1) * bsiz - 1)) % mod;
    int id, q;
    std::cin >> id >> q;
    for (int i = 0; i < q; ++i)
    {
        int n, m;
        std::cin >> n >> m;
        int br = m / bsiz, res = 0;
        for (int j = 0; j < br; ++j)
            res = (res + sum[n][j]) % mod;
        for (int j = br * bsiz; j <= m; ++j)
            res = (res + C(n, j)) % mod;
        std::cout << (res + mod) % mod << '\n';
    }
    return 0;
}