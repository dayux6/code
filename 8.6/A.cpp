#include <bits/stdc++.h>

const int maxn = 100, maxlg = 59;

template <typename T>
void chkmax(T &x, T y)
{
    if (x < y)
        x = y;
}

template <typename T>
void read(T &x)
{
    x = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
    {
        x = x * 10 + (c ^ 48);
        c = getchar();
    }
}

bool vis[maxlg + 1];

struct matrix
{
    int n;
    long long a[maxn + 1][maxn + 1];
} pw[maxlg + 1];

void mul(matrix &res, matrix x, matrix y)
{
    for (int i = 1; i <= res.n; ++i)
        std::fill_n(res.a[i] + 1, res.n, 0);

    for (int i = 1; i <= res.n; ++i)
        for (int k = 1; k <= x.n; ++k)
            for (int j = 1; j <= res.n; ++j)
                if (x.a[i][k] && y.a[k][j])
                    chkmax(res.a[i][j], x.a[i][k] + y.a[k][j]);
}

long long solve()
{
    int n;
    long long m;
    read(n);
    read(m);
    pw[0].n = n;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            read(pw[0].a[i][j]);

    vis[0] = true;
    std::fill_n(vis + 1, log2(m), false);
    long long ret = 0, stp = 0;
    matrix res, tmp;
    res.n = tmp.n = n;
    while (stp >= 0)
    {
        if (!vis[stp])
        {
            pw[stp].n = n;
            mul(pw[stp], pw[stp - 1], pw[stp - 1]);
            vis[stp] = true;
        }

        if (ret)
            mul(tmp, res, pw[stp]);
        else
            tmp = pw[stp];

        bool flg = false;
        for (int i = 1; i <= n; ++i)
            if (tmp.a[1][i] >= m)
            {
                flg = true;
                break;
            }

        if (!flg)
        {
            ret += 1ll << stp;
            ++stp;
            res = tmp;
        }
        else
            --stp;
    }

    return ret + 1;
}

int main()
{
    freopen("A.in", "r", stdin);
    int t;
    read(t);
    for (int _ = 0; _ < t; ++_)
        std::cout << solve() << std::endl;
    return 0;
}