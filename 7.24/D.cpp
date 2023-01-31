#include <bits/stdc++.h>

int n, rnk, **a, **b;
bool **flg;

void dfs(int x, int y)
{
    if (x == n)
    {
        ++rnk;
        bool same = true;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (a[i][j] != b[i][j])
                {
                    same = false;
                    break;
                }
        if (same)
        {
            std::cout << rnk << std::endl;
            exit(0);
        }
        return;
    }
    for (int i = 1; i <= n; ++i)
        if (!flg[x][i] && (x == 0 || b[x - 1][y] != i))
        {
            b[x][y] = i;
            flg[x][i] = true;
            if (y == n - 1)
                dfs(x + 1, 0);
            else
                dfs(x, y + 1);
            flg[x][i] = false;
        }
}

int main()
{
    freopen("D.in", "r", stdin);
    std::cin >> n;
    a = new int *[n];
    b = new int *[n];
    flg = new bool *[n];
    for (int i = 0; i < n; ++i)
    {
        a[i] = new int[n];
        b[i] = new int[n];
        flg[i] = new bool[n + 1]();
        for (int j = 0; j < n; ++j)
            std::cin >> a[i][j];
    }
    dfs(0, 0);
    return 0;
}