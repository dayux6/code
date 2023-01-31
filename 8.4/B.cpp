#include <bits/stdc++.h>

const int maxk = 6e3;

struct point
{
    int x, y;
} p[maxk + 1];

int k, fa[maxk + 2];
long long ans, dis[maxk + 2];
bool vis[maxk + 2];

int main()
{
    freopen("B.in", "r", stdin);
    int n, m;
    std::cin >> n >> m >> k;
    for (int i = 1; i <= k; ++i)
        std::cin >> p[i].x >> p[i].y;

    dis[0] = 0;
    long long ans = 0;
    for (int i = 0; i <= k + 1; ++i)
    {
        int pos;
        long long min = LLONG_MAX;
        for (int j = 0; j <= k + 1; ++j)
            if (!vis[j] && dis[j] < min)
            {
                pos = j;
                min = dis[j];
            }

        ans = std::max(ans, min);
        if (pos == k + 1)
            break;

        vis[pos] = true;
        if (pos)
        {
            for (int j = 0; j <= k; ++j)
                dis[j] = std::min(dis[j], 1ll * (p[pos].x - p[j].x) * (p[pos].x - p[j].x) + 1ll * (p[pos].y - p[j].y) * (p[pos].y - p[j].y));
            dis[k + 1] = std::min(dis[k + 1], 1ll * (m - p[pos].y) * (m - p[pos].y));
        }
        else
        {
            for (int j = 1; j <= k; ++j)
                dis[j] = 1ll * p[j].y * p[j].y;
            dis[k + 1] = 1ll * m * m;
        }
    }

    std::cout << std::fixed << std::setprecision(8) << sqrt(ans) / 2 << std::endl;
    return 0;
}