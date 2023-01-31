#include <bits/stdc++.h>

const int maxn = 2e5, maxk = 20, maxa = 1e7;

int a[maxn + 1], c[maxa + 1], lim[maxn + 1][maxk + 1], f[maxn + 1][maxk + 1];

int main()
{
#ifndef ONLINE_JUDGE
    std::freopen("CF1497E.in", "r", stdin);
#endif

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--)
    {
        int n, k;
        std::cin >> n >> k;

        int tot = 0;
        for (int i = 1; i <= n; ++i)
        {
            std::cin >> a[i];

            int x = a[i];
            for (int j = 2; j * j <= x; ++j)
                if (x % j == 0)
                {
                    int cnt = 0;
                    while (x % j == 0)
                    {
                        x /= j;
                        ++cnt;
                    }

                    for (int l = 0; l < (cnt / 2) * 2; ++l)
                        a[i] /= j;
                }

            tot = std::max(tot, a[i]);
        }

        for (int i = 0; i <= k; ++i)
        {
            std::fill_n(c + 1, tot, 0);
            int cnt = 0, l = 1;
            for (int r = 1; r <= n; ++r)
            {
                ++c[a[r]];
                if (c[a[r]] >= 2)
                    ++cnt;

                while (cnt > i)
                {
                    if (c[a[l]] >= 2)
                        --cnt;
                    --c[a[l]];
                    ++l;
                }

                lim[r][i] = l;
            }
        }

        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= k; ++j)
                f[i][j] = INT_MAX / 2;
        f[0][0] = 0;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 0; j <= k; ++j)
                for (int l = 0; l <= j; ++l)
                    f[i][j] = std::min(f[i][j], f[lim[i][l] - 1][j - l] + 1);
        }

        int min = INT_MAX;
        for (int i = 0; i <= k; ++i)
            min = std::min(min, f[n][i]);

        std::cout << min << std::endl;
    }
    return 0;
}