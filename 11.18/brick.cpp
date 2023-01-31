#include <bits/stdc++.h>

const int maxn = 5e3;

int a[maxn + 1], pre[maxn + 1], f[maxn + 1][maxn + 1];

int main()
{
    std::freopen("brick.in", "r", stdin);
    std::freopen("brick.out", "w", stdout);

    int n;
    std::cin >> n;

    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= i - 1; ++j)
            pre[j] = std::max(pre[j - 1], f[j][i - 1]);

        f[i][i] = pre[i - 1];
        int cur = a[i], p = i, s = 0, c = 0;
        for (int j = i + 1; j <= n; ++j)
        {
            while (p - 1 >= 2 && s + a[p - 1] <= cur)
            {
                --p;
                s += a[p];
            }

            if (s == cur)
                ++c;

            f[i][j] = std::max(f[i][j - 1], pre[p - 1] + c);

            cur += a[j];
        }
    }

    int max = 0;
    for (int i = 1; i <= n; ++i)
        max = std::max(max, f[i][n]);
    std::cout << max << std::endl;
    return 0;
}