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

const int maxn = 1e3, maxlg = 10;

int s[maxn + 1][maxn + 1], min[maxn + 1][maxn + 1][maxlg + 1];

int main()
{
    std::freopen("trip.in", "r", stdin);
    std::freopen("trip.out", "w", stdout);

    int n, m, a, b, c, d;
    read(m);
    read(n);
    read(b);
    read(a);
    read(d);
    read(c);

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            read(s[i][j]);
            s[i][j] += s[i][j - 1];
        }

        for (int j = 1; j <= m; ++j)
            s[i][j] += s[i - 1][j];
    }

    auto calc = [&](int x1, int y1, int x2, int y2)
    { return s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + s[x1 - 1][y1 - 1]; };

    for (int i = 0; i < c; ++i)
        for (int j = 0; j < d; ++j)
            for (int k = 0; (1 << k) <= n; ++k)
                min[j][i][k] = INT_MAX;
    for (int i = c; i <= n; ++i)
        for (int j = d; j <= m; ++j)
            min[j][i][0] = calc(i - c + 1, j - d + 1, i, j);
    for (int j = d; j <= m; ++j)
        for (int k = 1; (1 << k) <= n; ++k)
            for (int i = c; i + (1 << k) - 1 <= n; ++i)
                min[j][i][k] = std::min(min[j][i][k - 1], min[j][i + (1 << (k - 1))][k - 1]);

    auto getmin = [&](int i, int l, int r)
    {
        int k = std::log2(r - l + 1);
        return std::min(min[i][l][k], min[i][r - (1 << k) + 1][k]);
    };
    int ans = 0;
    for (int i = a; i <= n; ++i)
    {
        std::multiset<int> ms;

        for (int j = d; j < b; ++j)
            ms.emplace(getmin(j, i - a + c + 1, i - 1));

        for (int j = b; j <= m; ++j)
        {
            auto it = ms.lower_bound(getmin(j - b + d, i - a + c + 1, i - 1));
            if (it != ms.end())
                ms.erase(it);
            ans = std::max(ans, calc(i - a + 1, j - b + 1, i, j) - *ms.begin());
            ms.emplace(getmin(j, i - a + c + 1, i - 1));
        }
    }

    std::cout << ans << std::endl;
    return 0;
}