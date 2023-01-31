#include <bits/stdc++.h>

const int maxn = 1e3, mod = 1e4 + 7;

int h[maxn + 1], ctl[maxn + 1][maxn + 1], ctr[maxn + 1][maxn + 2], cbl[maxn + 2][maxn + 1], cbr[maxn + 2][maxn + 2];
char c[maxn + 1][maxn + 1];

int main()
{
    std::freopen("fire.in", "r", stdin);
    std::freopen("fire.out", "w", stdout);

    int n;
    std::cin >> n;

    for (int i = 1; i <= n; ++i)
        std::scanf("%s", c[i] + 1);

    std::vector<int> s;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
            if (c[i][j] == 'B')
                h[j] = 0;
            else
                ++h[j];

        s.clear();
        for (int j = 1; j <= n; ++j)
        {
            while (!s.empty() && h[s.back()] >= h[j])
                s.pop_back();
            int l = s.empty() ? 0 : s.back();
            ctl[i][j] = (ctl[i][l] + (j - l) * h[j] % mod) % mod;
            s.emplace_back(j);
        }

        s.clear();
        for (int j = n; j >= 1; --j)
        {
            while (!s.empty() && h[s.back()] >= h[j])
                s.pop_back();
            int r = s.empty() ? n + 1 : s.back();
            ctr[i][j] = (ctr[i][r] + (r - j) * h[j] % mod) % mod;
            s.emplace_back(j);
        }
    }

    std::fill_n(h + 1, n, 0);
    for (int i = n; i >= 1; --i)
    {
        for (int j = 1; j <= n; ++j)
            if (c[i][j] == 'B')
                h[j] = 0;
            else
                ++h[j];

        s.clear();
        for (int j = 1; j <= n; ++j)
        {
            while (!s.empty() && h[s.back()] >= h[j])
                s.pop_back();
            int l = s.empty() ? 0 : s.back();
            cbl[i][j] = (cbl[i][l] + (j - l) * h[j] % mod) % mod;
            s.emplace_back(j);
        }

        s.clear();
        for (int j = n; j >= 1; --j)
        {
            while (!s.empty() && h[s.back()] >= h[j])
                s.pop_back();
            int r = s.empty() ? n + 1 : s.back();
            cbr[i][j] = (cbr[i][r] + (r - j) * h[j] % mod) % mod;
            s.emplace_back(j);
        }
    }

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            ctl[i][j] = std::max(0, ctl[i][j] - 1);
            ctr[i][j] = std::max(0, ctr[i][j] - 1);
            cbl[i][j] = std::max(0, cbl[i][j] - 1);
            cbr[i][j] = std::max(0, cbr[i][j] - 1);
        }

    int sum = 0, ans = 0;
    for (int i = 1; i < n; ++i)
    {
        for (int j = 1; j <= n; ++j)
            sum = (sum + ctl[i][j]) % mod;
        for (int j = 1; j <= n; ++j)
            ans = (ans + sum * cbl[i + 1][j] % mod) % mod;
    }

    sum = 0;
    for (int j = 1; j < n; ++j)
    {
        for (int i = 1; i <= n; ++i)
            sum = (sum + ctl[i][j]) % mod;
        for (int i = 1; i <= n; ++i)
            ans = (ans + sum * ctr[i][j + 1] % mod) % mod;
    }

    for (int i = n; i >= 1; --i)
    {
        for (int j = 1; j <= n; ++j)
            cbl[i][j] = (cbl[i][j] + cbl[i][j - 1]) % mod;
        for (int j = 1; j <= n; ++j)
            cbl[i][j] = (cbl[i][j] + cbl[i + 1][j]) % mod;
    }

    for (int i = n; i >= 1; --i)
    {
        for (int j = n; j >= 1; --j)
            cbr[i][j] = (cbr[i][j] + cbr[i][j + 1]) % mod;
        for (int j = 1; j <= n; ++j)
            cbr[i][j] = (cbr[i][j] + cbr[i + 1][j]) % mod;
    }

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            ans = (ans - ctl[i][j] * cbr[i + 1][j + 1] % mod - ctr[i][j] * cbl[i + 1][j - 1] % mod) % mod;

    std::cout << (ans + mod) % mod << std::endl;
    return 0;
}