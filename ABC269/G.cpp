#include <bits/stdc++.h>

const int maxn = 2e5, maxm = 2e5;

int a[maxn + 1], b[maxn + 1], f[maxm + 1];

std::unordered_map<int, int> c;

std::vector<std::pair<int, int>> vct;

int main()
{
    freopen("G.in", "r", stdin);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, m;
    std::cin >> n >> m;

    int sum = 0;
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> a[i] >> b[i];
        sum += a[i];
        if (a[i] != b[i])
            ++c[b[i] - a[i]];
    }

    for (auto pr : c)
    {
        int sum = 0;
        for (int i = 1; sum + i <= pr.second; i <<= 1)
        {
            vct.emplace_back(pr.first * i, i);
            sum += i;
        }
        if (sum < pr.second)
            vct.emplace_back(pr.first * (pr.second - sum), pr.second - sum);
    }

    std::fill_n(f, m + 1, INT_MAX / 2);
    f[sum] = 0;
    for (auto pr : vct)
        if (pr.first < 0)
            for (int i = -pr.first; i <= m; ++i)
                f[i + pr.first] = std::min(f[i + pr.first], f[i] + pr.second);
        else
            for (int i = m; i >= pr.first; --i)
                f[i] = std::min(f[i], f[i - pr.first] + pr.second);

    for (int i = 0; i <= m; ++i)
        if (f[i] > n)
            std::cout << -1 << std::endl;
        else
            std::cout << f[i] << std::endl;
    return 0;
}