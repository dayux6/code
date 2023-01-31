#include <bits/stdc++.h>

#define int long long

const int maxn = 1e5;

int res, tot, c[maxn + 1], w[maxn + 1][2], f[maxn + 1][2];
std::vector<int> s[maxn + 1];

void ins(int x, bool b)
{
    if (c[x] == 0)
    {
        ++tot;
        res += f[x][b];
    }
    else
        res = res - f[x][b ^ 1] + std::max(f[x][b], f[x][b ^ 1]);

    ++c[x];
}

void del(int x, int b)
{
    if (c[x] == 1)
    {
        --tot;
        res -= f[x][b];
    }
    else
        res = res - std::max(f[x][b], f[x][b ^ 1]) + f[x][b ^ 1];

    --c[x];
}

void dp(int x)
{
    f[x][0] = w[x][0];
    f[x][1] = w[x][1];

    if (!s[x].empty())
    {
        std::vector<std::pair<int, int>> vct;

        for (int v : s[x])
        {
            dp(v);

            if (f[v][0] != LLONG_MIN)
                vct.emplace_back(v, 0);
            if (f[v][1] != LLONG_MIN)
                vct.emplace_back(v, 1);
        }

        auto calc = [&](bool b)
        {
            vct.emplace_back(x, b);

            std::sort(vct.begin(), vct.end(), [](std::pair<int, int> x, std::pair<int, int> y)
                      { return w[x.first][x.second] < w[y.first][y.second]; });

            int ret = LLONG_MIN;
            for (int lim = 0; lim <= 100; ++lim)
            {
                std::size_t r = 0;
                for (std::size_t l = 0; l < vct.size(); ++l)
                {
                    while (r < vct.size() && std::ceil((w[vct[r].first][vct[r].second] - w[vct[l].first][vct[l].second]) / 1e3) <= lim)
                    {
                        ins(vct[r].first, vct[r].second);
                        ++r;
                    }

                    if (tot == s[x].size() + 1)
                        ret = std::max(ret, res - lim * 666 * x);

                    del(vct[l].first, vct[l].second);
                }
            }

            for (std::size_t i = 0; i < vct.size(); ++i)
                if (vct[i].first == x)
                {
                    vct.erase(vct.begin() + i);
                    break;
                }

            return ret;
        };

        f[x][0] = calc(0);
        f[x][1] = calc(1);
    }
}

signed main()
{
    std::freopen("lele.in", "r", stdin);
    std::freopen("lele.out", "w", stdout);

    int n;
    std::cin >> n;

    for (int i = 1; i <= n; ++i)
        std::cin >> w[i][0] >> w[i][1];

    for (int i = 2, fa; i <= n; ++i)
    {
        std::cin >> fa;
        s[fa].emplace_back(i);
    }

    dp(1);

    std::cout << std::max(f[1][0], f[1][1]) << std::endl;
    return 0;
}