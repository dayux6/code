#include <bits/stdc++.h>

const int maxn = 2000, maxq = 1e4;

int ans[maxq];
std::pair<int, int> pr[maxq];
std::bitset<maxn + 1> e[maxn + 1];

int main()
{
    std::freopen("Ex.in", "r", stdin);

    int n, m;
    std::cin >> n >> m;

    for (int i = 0, u, v; i < m; ++i)
    {
        std::cin >> u >> v;
        e[u].set(v);
    }

    int q;
    std::cin >> q;
    std::fill_n(ans, q, -1);
    for (int i = 0; i < q; ++i)
    {
        std::cin >> pr[i].first >> pr[i].second;

        if (e[pr[i].first][pr[i].second])
            ans[i] = std::max(pr[i].first, pr[i].second);
    }

    for (int k = 1; k <= n; ++k)
    {
        for (int i = 1; i <= n; ++i)
            if (e[i][k])
                e[i] |= e[k];

        for (int i = 0; i < q; ++i)
            if (ans[i] == -1 && e[pr[i].first][pr[i].second])
                ans[i] = std::max(k, std::max(pr[i].first, pr[i].second));
    }

    for (int i = 0; i < q; ++i)
        std::cout << ans[i] << std::endl;
    return 0;
}