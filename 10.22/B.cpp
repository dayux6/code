#include <bits/stdc++.h>

const int maxn = 70, maxt = 30;

struct book
{
    int h, t;

    bool operator<(book rhs) const { return h > rhs.h; }
} b[maxn + 1];

int f[maxn * maxt + 1][maxn * maxt + 1][3][2];

int main()
{
    std::freopen("book.in", "r", stdin);
    std::freopen("book.out", "w", stdout);

    int n;
    std::cin >> n;

    for (int i = 1; i <= n; ++i)
        std::cin >> b[i].h >> b[i].t;

    std::sort(b + 1, b + n + 1);
    f[0][0][0][0] = f[0][0][1][0] = f[0][0][2][0] = 0;
    int sumt = 0;
    for (int i = 1; i <= n; ++i)
    {
        bool k = i & 1;

        for (int j = 0; j <= sumt + b[i].t; ++j)
            for (int l = 0; l <= sumt + b[i].t; ++l)
                f[j][l][0][k] = f[j][l][1][k] = f[j][l][2][k] = INT_MAX;

        for (int j = 0; j <= sumt; ++j)
            for (int l = 0; l <= sumt; ++l)
                if (f[j][l][0][k ^ 1] != INT_MAX && f[j][l][1][k ^ 1] != INT_MAX && f[j][l][2][k ^ 1] != INT_MAX)
                {
                    if (std::max(b[i].h, f[j][l][0][k ^ 1]) + f[j][l][1][k ^ 1] + f[j][l][2][k ^ 1] <= f[j + b[i].t][l][0][k] + f[j + b[i].t][l][1][k] + f[j + b[i].t][l][2][k])
                    {
                        f[j + b[i].t][l][0][k] = std::max(b[i].h, f[j][l][0][k ^ 1]);
                        f[j + b[i].t][l][1][k] = f[j][l][1][k ^ 1];
                        f[j + b[i].t][l][2][k] = f[j][l][2][k ^ 1];
                    }

                    if (f[j][l][0][k ^ 1] + std::max(b[i].h, f[j][l][1][k ^ 1]) + f[j][l][2][k ^ 1] <= f[j][l + b[i].t][0][k] + f[j][l + b[i].t][1][k] + f[j][l + b[i].t][2][k])
                    {
                        f[j][l + b[i].t][0][k] = f[j][l][0][k ^ 1];
                        f[j][l + b[i].t][1][k] = std::max(b[i].h, f[j][l][1][k ^ 1]);
                        f[j][l + b[i].t][2][k] = f[j][l][2][k ^ 1];
                    }

                    if (std::max(b[i].h, f[j][l][0][k ^ 1]) + f[j][l][1][k ^ 1] + f[j][l][2][k ^ 1] <= f[j][l][1][k] + f[j][l][0][k] + f[j][l][2][k])
                    {
                        f[j][l][0][k] = f[j][l][0][k ^ 1];
                        f[j][l][1][k] = f[j][l][1][k ^ 1];
                        f[j][l][2][k] = std::max(b[i].h, f[j][l][2][k ^ 1]);
                    }
                }

        sumt += b[i].t;
    }

    int ans = INT_MAX;
    bool k = n & 1;
    for (int i = 1; i < sumt; ++i)
        for (int j = 1; i + j < sumt; ++j)
            if (f[i][j][0][k] != INT_MAX && f[i][j][1][k] != INT_MAX && f[i][j][2][k] != INT_MAX)
                ans = std::min(ans, std::max({i, j, sumt - i - j}) * (f[i][j][0][k] + f[i][j][1][k] + f[i][j][2][k]));
    std::cout << ans << std::endl;
    return 0;
}