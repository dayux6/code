#include <bits/stdc++.h>

const int maxn = 1e6;

int a[maxn + 1], c[maxn + 1];

long long solve()
{
    int n, m;
    std::cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];

    long long ret = 0;
    for (int l = 1; l <= n; ++l)
    {
        std::fill_n(c + 1, m, 0);

        int p = l;

        for (int r = l + m - 1; r <= n; r += m)
        {
            while (p <= r)
            {
                ++c[a[p]];
                ++p;
            }

            int tmp = (r - l + 1) / m;
            bool flg = true;
            for (int j = 1; j <= m; ++j)
                if (c[j] != tmp)
                {
                    flg = false;
                    break;
                }

            ret += flg;
        }
    }

    return ret;
}

int main()
{
    std::freopen("resona.in", "r", stdin);
    std::freopen("resona.ans", "w", stdout);

    int t;
    std::cin >> t;

    for (int i = 0; i < t; ++i)
        std::cout << solve() << std::endl;
    return 0;
}