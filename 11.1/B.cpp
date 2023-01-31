#include <bits/stdc++.h>

const int maxn = 10;

char c[1 << (maxn - 1)][1 << (maxn - 1)];

void dfs(int n, int x, int y)
{
    if (n == 1)
    {
        c[x][y] = '*';
        return;
    }
    else
    {
        dfs(n - 1, x, y);
        int len = 1 << (n - 2);
        dfs(n - 1, x, y + len);
        dfs(n - 1, x + len, y);
    }
}

int main()
{
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);

    int n;
    std::cin >> n;
    for (int i = 0; i < (1 << (n - 1)); ++i)
        for (int j = 0; j < (1 << (n - 1)) - i; ++j)
            c[i][j] = ' ';
    dfs(n, 0, 0);
    for (int i = 0; i < (1 << (n - 1)); ++i)
    {
        for (int j = 0; j < (1 << (n - 1)) - i; ++j)
        {
            putchar(c[i][j]);
            putchar(' ');
        }
        putchar('\n');
    }
    return 0;
}