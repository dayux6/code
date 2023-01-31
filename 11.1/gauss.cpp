#include <bits/stdc++.h>

typedef long double db;

const int maxn = 100;

db e[maxn][maxn + 1];

int main()
{
    freopen("gauss.in", "r", stdin);

    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= n; ++j)
            std::cin >> e[i][j];

    for (int i = 0; i < n; ++i)
    {
        int p = i;
        for (int j = i + 1; j < n; ++j)
            if (std::abs(e[j][i]) > std::abs(e[p][i]))
                p = j;
        std::swap(e[i], e[p]);

        if (e[i][i] == 0)
        {
            std::puts("No Solution");
            return 0;
        }

        db tmp = e[i][i];
        for (int j = 0; j <= n; ++j)
            e[i][j] /= tmp;

        for (int j = 0; j < n; ++j)
            if (i != j)
            {
                tmp = e[j][i];
                for (int k = 0; k <= n; ++k)
                    e[j][k] -= tmp * e[i][k];
            }
    }

    for (int i = 0; i < n; ++i)
        std::cout << std::fixed << std::setprecision(2) << e[i][n] << std::endl;
    return 0;
}