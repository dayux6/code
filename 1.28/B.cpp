#include <bits/stdc++.h>

typedef long double db;

const int maxn = 6, maxm = 100;

int m, cnt, vis[maxm + 1], match[maxm + 1];
bool e[maxn + 1][maxm + 1];
db p[maxn + 1][maxm + 1];
std::random_device seed;
std::mt19937 rnd(seed());
std::uniform_real_distribution<db> gen(0, 1);

bool Hungary(int x)
{
    for (int i = 1; i <= m; ++i)
        if (e[x][i] && vis[i] != cnt)
        {
            vis[i] = cnt;

            if (match[i] == 0 || Hungary(match[i]))
            {
                match[i] = x;
                return true;
            }
        }

    return false;
}

int main()
{
    std::freopen("match.in", "r", stdin);
    std::freopen("match.out", "w", stdout);

    int n;
    std::cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            std::cin >> p[i][j];

    int sum = 0, tot = 0;
    while (std::clock() <= 0.99 * CLOCKS_PER_SEC)
    {
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                e[i][j] = gen(rnd) < p[i][j];

        std::fill_n(match + 1, m, 0);
        for (int i = 1; i <= n; ++i)
        {
            ++cnt;
            sum += Hungary(i);
        }

        ++tot;
    }

    std::cout << std::fixed << std::setprecision(2) << std::round(1e2 * sum / tot) / 1e2 << std::endl;
    return 0;
}