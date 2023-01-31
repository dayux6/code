#include <bits/stdc++.h>

const int maxn = 500;

int a[maxn + 1][maxn + 1], s[maxn][maxn];

int main()
{
    std::freopen("matrix.in", "r", stdin);
    std::freopen("matrix.out", "w", stdout);

    int n, m, t;
    std::cin >> n >> m >> t;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            std::cin >> a[i][j];

    for (int i = 1; i < n; ++i)
        for (int j = 1; j < m; ++j)
            s[i][j] = a[i][j] + a[i + 1][j + 1] == a[i + 1][j] + a[i][j + 1];

    for (int i = 1; i < n; ++i)
    {
        for (int j = 1; j < m; ++j)
            s[i][j] += s[i][j - 1];
        for (int j = 1; j < m; ++j)
            s[i][j] += s[i - 1][j];
    }

    auto query = [&](int t, int l, int b, int r)
    { return s[b][r] - s[t - 1][r] - s[b][l - 1] + s[t - 1][l - 1]; };

    for (int i = 0, x, y, k; i < t; ++i)
    {
        std::cin >> x >> y >> k;
        if (query(x, y, x + k - 2, y + k - 2) == (k - 1) * (k - 1))
            std::putchar('Y');
        else
            std::putchar('N');
        std::putchar('\n');
    }
    return 0;
}