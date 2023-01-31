#include <bits/stdc++.h>

const int maxn = 5e3, maxm = 10, maxh = 24;

int h, t[maxn + 1];
std::pair<int, int> f[maxn + 1][maxh], g[1 << maxm][maxh];
std::vector<int> s[maxn + 1];

void dfs(int x)
{
    for (int v : s[x])
        dfs(v);

    for (int i = 0; i < h; ++i)
    {
        if (i + t[x] <= h)
            g[0][i] = std::make_pair(0, i + t[x]);
        else
            g[0][i] = std::make_pair(1, t[x]);

        if (g[0][i].second == h)
        {
            ++g[0][i].first;
            g[0][i].second = 0;
        }
    }
    for (int i = 1; i < (1 << s[x].size()); ++i)
        for (int j = 0; j < h; ++j)
        {
            g[i][j] = std::make_pair(INT_MAX, INT_MAX);
            for (int k = 0; k < s[x].size(); ++k)
                if ((i >> k) & 1)
                    g[i][j] = std::min(g[i][j], std::make_pair(g[i ^ (1 << k)][j].first + f[s[x].at(k)][g[i ^ (1 << k)][j].second].first, f[s[x].at(k)][g[i ^ (1 << k)][j].second].second));
        }

    for (int i = 0; i < h; ++i)
        f[x][i] = g[(1 << s[x].size()) - 1][i];
}

int main()
{
    freopen("B.in", "r", stdin);
    int n;
    std::cin >> n >> h;

    for (int i = 1; i <= n; ++i)
        std::cin >> t[i];

    for (int i = 1; i <= n; ++i)
    {
        int m;
        std::cin >> m;
        for (int j = 0; j < m; ++j)
        {
            int x;
            std::cin >> x;
            s[i].push_back(x);
        }
    }

    dfs(1);

    if (f[1][0].second != 0)
        ++f[1][0].first;
    std::cout << f[1][0].first << std::endl;
    return 0;
}