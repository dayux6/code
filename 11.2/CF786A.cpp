#include <bits/stdc++.h>

const int maxn = 7e3;

int n, k[2], s[maxn][2], cnt[maxn + 1][2];
bool vis[maxn + 1][2], win[maxn + 1][2];

void dfs(int x, bool b)
{
    if (vis[x][b])
        return;

    vis[x][b] = true;
    for (int i = 1; i <= k[b ^ 1]; ++i)
    {
        int pre = (x + n - s[i][b ^ 1]) % n;

        if (pre == 0)
            pre = n;

        if (pre != 1)
        {
            if (!win[x][b])
            {
                win[pre][b ^ 1] = true;
                dfs(pre, b ^ 1);
            }
            else
            {
                ++cnt[pre][b ^ 1];

                if (cnt[pre][b ^ 1] == k[b ^ 1])
                    dfs(pre, b ^ 1);
            }
        }
    }
}

int main()
{
    freopen("CF786A.in", "r", stdin);

    std::cin >> n;

    for (int i = 0; i < 2; ++i)
    {
        std::cin >> k[i];

        for (int j = 1; j <= k[i]; ++j)
            std::cin >> s[j][i];
    }

    for (int i = 0; i < 2; ++i)
        dfs(1, i);

    for (int i = 0; i < 2; ++i)
    {
        for (int j = 2; j <= n; ++j)
            if (vis[j][i])
            {
                if (win[j][i])
                    std::cout << "Win ";
                else
                    std::cout << "Lose ";
            }
            else
                std::cout << "Loop ";
        std::cout << std::endl;
    }
    return 0;
}