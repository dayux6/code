#include <bits/stdc++.h>

const int maxn = 2e3;

bool vis[maxn + 1];

struct fish
{
    int w, x, v;
} f[maxn + 1];

int main()
{
    std::freopen("F.in", "r", stdin);

    int n, len;
    std::cin >> n >> len;

    for (int i = 1; i <= n; ++i)
        std::cin >> f[i].w >> f[i].x >> f[i].v;

    int ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        std::multiset<std::pair<long double, int>> s;
        for (int j = 1; j <= n; ++j)
        {
            int dx = f[j].x - f[i].x, dv = f[j].v - f[i].v;

            if (dv == 0)
            {
                if (dx >= 0 && dx <= len)
                    s.emplace(0, j);
            }
            else if (dv < 0)
            {
                s.emplace(-1.0 * dx / dv, j);
                s.emplace(-1.0 * (dx - len) / dv, j);
            }
            else
            {
                s.emplace(-1.0 * (dx - len) / dv, j);
                s.emplace(-1.0 * dx / dv, j);
            }
        }

        int sum = 0;
        std::fill_n(vis + 1, n, false);
        for (std::pair<long double, int> pr : s)
        {
            if (!vis[pr.second])
            {
                sum += f[pr.second].w;
                vis[pr.second] = true;
            }
            else
            {
                sum -= f[pr.second].w;
                vis[pr.second] = false;
            }

            if (pr.first >= 0)
                ans = std::max(ans, sum);
        }
    }

    std::cout << ans << std::endl;
    return 0;
}