#include <bits/stdc++.h>

const int maxn = 5e3;

std::pair<int, int> pr[maxn + 1];

int main()
{
    std::freopen("rewrite.in", "r", stdin);
    std::freopen("rewrite.out", "w", stdout);

    int n;
    std::cin >> n;

    int liml = 0, limr = INT_MAX;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> pr[i].first >> pr[i].second;
        liml = std::max(liml, pr[i].first);
        limr = std::min(limr, pr[i].second);
    }

    if (!(n & 1))
    {
        pr[n].first = pr[n].second = ((long long)liml + limr) / 2;
        ++n;
    }

    std::sort(pr, pr + n, [](std::pair<int, int> x, std::pair<int, int> y)
              { return x.second - x.first < y.second - y.first; });

    long long f[2][2][n / 2 + 1];
    for (int i = 0; i < 2; ++i)
        std::fill_n(f[1][i], n / 2 + 1, LLONG_MAX / 2);
    f[1][0][0] = 0;
    for (int i = 0; i < n; ++i)
    {
        bool b = i & 1;
        for (int j = 0; j < 2; ++j)
            std::fill_n(f[b][j], n / 2 + 1, LLONG_MAX / 2);
        for (int j = 0; j <= n / 2; ++j)
        {
            for (int k = 0; k < 2; ++k)
                f[b][k][j] = std::min(f[b ^ 1][k][j] - pr[i].first + 1ll * (pr[i].second - pr[i].first) * ((n / 2) - ((i + 1) - j - (int)k)), j == 0 ? (LLONG_MAX / 2) : (f[b ^ 1][k][j - 1] + pr[i].second + 1ll * (pr[i].second - pr[i].first) * ((n / 2) - j)));
            f[b][1][j] = std::min(f[b][1][j], f[b ^ 1][0][j] + 1ll * (n / 2) * (pr[i].second - pr[i].first));
        }
    }

    std::cout << f[0][1][n / 2] << std::endl;
    return 0;
}