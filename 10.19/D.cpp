#include <bits/stdc++.h>

void read(int &x)
{
    x = 0;
    char c = std::getchar();

    while (!std::isdigit(c))
        c = std::getchar();
    while (std::isdigit(c))
    {
        x = x * 10 + (c ^ 48);
        c = std::getchar();
    }
}

void write(int x)
{
    static int t = 0, s[10];

    do
    {
        s[t] = x % 10;
        x /= 10;
        ++t;
    } while (x != 0);

    while (t > 0)
    {
        --t;
        putchar(s[t] + 48);
    }
    putchar('\n');
}

const int maxlg = 20, mod = 1e9 + 7;

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

int m, s[maxlg + 1], inv[maxlg + 2];

void dfs(int d, int x, int pre, int c, int v)
{
    s[d] = (s[d] + v) % mod;

    if (1ll * x * pre <= m)
        dfs(d + 1, x * pre, pre, c + 1, 1ll * v * inv[c + 1] % mod);
    for (int i = pre + 1; 1ll * x * i <= m; ++i)
        dfs(d + 1, x * i, i, 1, v);
}

int main()
{
    std::freopen("sequence.in", "r", stdin);
    std::freopen("sequence.out", "w", stdout);

    int q;
    read(m);
    read(q);

    for (int i = 1; i <= maxlg + 1; ++i)
        inv[i] = qpow(i);
    s[0] = 1;
    for (int i = 2; i <= m; ++i)
        dfs(1, i, i, 1, 1);

    for (int i = 0; i < q; ++i)
    {
        int n;
        read(n);

        int C = 1, fac = 1, res = 0;
        for (int j = 0; j <= maxlg; ++j)
        {
            C = 1ll * C * (n - j + 1) % mod * inv[j + 1] % mod;
            res = (res + 1ll * C * fac % mod * s[j] % mod) % mod;
            fac = 1ll * fac * (j + 1) % mod;
        }

        write((res - 1 + mod) % mod);
    }
    return 0;
}