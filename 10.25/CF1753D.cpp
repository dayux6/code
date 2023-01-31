#include <bits/stdc++.h>

const int maxn = 3e5;

std::array<long long, maxn + 1> dis;
std::array<bool, maxn + 1> vis;

struct edge
{
    int v, w;

    edge(int _v, int _w) : v(_v), w(_w) {}
};
std::array<std::vector<edge>, maxn + 1> g;

int main()
{
    std::freopen("CF1753D.in", "r", stdin);

    int n, m, p, q;
    std::cin >> n >> m >> p >> q;

    char **c = new char *[n + 1];
    for (int i = 1; i <= n; ++i)
    {
        c[i] = new char[m + 2];
        std::scanf("%s", c[i] + 1);
    }

    auto check = [&](int x, int y)
    { return x >= 1 && x <= n && y >= 1 && y <= m && c[x][y] != '#'; };
    auto calc = [&](int x, int y)
    { return (x - 1) * m + y; };

    std::fill_n(dis.begin() + 1, n * m, LLONG_MAX);
    std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<std::pair<long long, int>>> h;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            switch (c[i][j])
            {
            case 'L':
            {
                if (check(i - 1, j))
                    g[calc(i - 1, j)].emplace_back(calc(i, j + 1), p);
                if (check(i + 1, j))
                    g[calc(i + 1, j)].emplace_back(calc(i, j + 1), p);
                if (check(i, j - 1))
                    g[calc(i, j - 1)].emplace_back(calc(i, j + 1), q);
                break;
            }
            case 'R':
            {
                if (check(i - 1, j))
                    g[calc(i - 1, j)].emplace_back(calc(i, j - 1), p);
                if (check(i + 1, j))
                    g[calc(i + 1, j)].emplace_back(calc(i, j - 1), p);
                if (check(i, j + 1))
                    g[calc(i, j + 1)].emplace_back(calc(i, j - 1), q);
                break;
            }
            case 'U':
            {
                if (check(i, j - 1))
                    g[calc(i, j - 1)].emplace_back(calc(i + 1, j), p);
                if (check(i, j + 1))
                    g[calc(i, j + 1)].emplace_back(calc(i + 1, j), p);
                if (check(i - 1, j))
                    g[calc(i - 1, j)].emplace_back(calc(i + 1, j), q);
                break;
            }
            case 'D':
            {
                if (check(i, j - 1))
                    g[calc(i, j - 1)].emplace_back(calc(i - 1, j), p);
                if (check(i, j + 1))
                    g[calc(i, j + 1)].emplace_back(calc(i - 1, j), p);
                if (check(i + 1, j))
                    g[calc(i + 1, j)].emplace_back(calc(i - 1, j), q);
                break;
            }
            case '.':
            {
                dis[calc(i, j)] = 0;
                h.emplace(0, calc(i, j));
                break;
            }
            }

    while (!h.empty())
    {
        int x = h.top().second;
        h.pop();

        if (!vis[x])
        {
            vis[x] = true;

            for (edge e : g[x])
                if (dis[e.v] > dis[x] + e.w)
                {
                    dis[e.v] = dis[x] + e.w;
                    h.emplace(dis[e.v], e.v);
                }
        }
    }

    long long min = LLONG_MAX;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (dis[calc(i, j)] != LLONG_MAX)
            {
                if (check(i + 1, j) && dis[calc(i + 1, j)] != LLONG_MAX)
                    min = std::min(min, dis[calc(i, j)] + dis[calc(i + 1, j)]);
                if (check(i, j + 1) && dis[calc(i, j + 1)] != LLONG_MAX)
                    min = std::min(min, dis[calc(i, j)] + dis[calc(i, j + 1)]);
            }

    if (min == LLONG_MAX)
        std::cout << -1 << std::endl;
    else
        std::cout << min << std::endl;
    return 0;
}