#include <bits/stdc++.h>

const int maxn = 250;

int a[maxn + 1], d[maxn + 1][maxn + 1], dis[(maxn + 1) * (maxn + 3)];

int main()
{
    int n, m;
    std::cin >> n >> m;

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> a[i];
        std::fill_n(d[i] + 1, n, INT_MAX);
    }

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        std::cin >> u >> v;
        d[u][v] = a[v];
    }

    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (d[i][k] ^ INT_MAX && d[k][j] ^ INT_MAX)
                    d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);

    auto calc = [=](int x, int y, bool b)
    { return b * (n + 1) * (n + 1) + x * (n + 1) + y; };

    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
            {
            }
    return 0;
}