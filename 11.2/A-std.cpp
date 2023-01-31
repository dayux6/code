#include <bits/stdc++.h>

namespace INPUT_SPACE
{
    const int S = (1 << 20) + 5;
    char B[S], *H, *T;
    inline int gc()
    {
        if (H == T)
            T = (H = B) + fread(B, 1, S, stdin);
        return (H == T) ? EOF : *H++;
    }
    inline void read(int &x)
    {
        x = 0;
        int ch;
        while ((ch = gc()) < '0' || ch > '9')
            ;
        x = ch ^ '0';
        while ((ch = gc()) >= '0' && ch <= '9')
            x = x * 10 + (ch ^ '0');
    }
}
using INPUT_SPACE::read;

const int maxn = 1e6, maxlg = 19;

int min[maxn + 1][maxlg + 1], max[maxn + 1][maxlg + 1];

int querymin(int l, int r)
{
    int k = std::log2(r - l + 1);
    return std::min(min[l][k], min[r - (1 << k) + 1][k]);
}

int querymax(int l, int r)
{
    int k = std::log2(r - l + 1);
    return std::max(max[l][k], max[r - (1 << k) + 1][k]);
}

int main()
{
    freopen("range.in", "r", stdin);
    freopen("range.out", "w", stdout);

    int n, m;
    read(n);
    read(m);
    std::unordered_map<int, int> pre;
    for (int i = 1; i <= n; ++i)
        min[i][0] = n + 1;
    for (int i = 1; i <= n; ++i)
    {
        int a;
        read(a);
        if (pre.count(a))
        {
            min[pre.at(a)][0] = i;
            max[i][0] = pre.at(a);
            pre.at(a) = i;
        }
        else
            pre.emplace(a, i);
    }

    for (int i = 1; i <= maxlg; ++i)
        for (int j = 1; j + (1 << i) - 1 <= n; ++j)
        {
            min[j][i] = std::min(min[j][i - 1], min[j + (1 << (i - 1))][i - 1]);
            max[j][i] = std::max(max[j][i - 1], max[j + (1 << (i - 1))][i - 1]);
        }

    for (int i = 0; i < m; ++i)
    {
        int l, r;
        read(l);
        read(r);
        if (querymax(l, r) < l && querymin(l, r) > r)
            putchar('1');
        else
            putchar('0');
        putchar('\n');
    }
    return 0;
}