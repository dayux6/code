#include <bits/stdc++.h>

int n, *p, **f[2];

int dfs(int l, int r, bool b)
{
    if (l == 0 && r == n - 1)
        return 0;
    if (f[b][l][r] != INT_MAX)
        return f[b][l][r];
    if (b)
        return f[b][l][r] = std::min(l ? dfs(l - 1, r, false) + (p[r] - p[l - 1]) * (n - r + l - 1) : INT_MAX, r ^ (n - 1) ? dfs(l, r + 1, true) + (p[r + 1] - p[r]) * (n - r + l - 1) : INT_MAX);
    else
        return f[b][l][r] = std::min(l ? dfs(l - 1, r, false) + (p[l] - p[l - 1]) * (n - r + l - 1) : INT_MAX, r ^ (n - 1) ? dfs(l, r + 1, true) + (p[r + 1] - p[l]) * (n - r + l - 1) : INT_MAX);
}

int main()
{
    freopen("E.in", "r", stdin);
    std::cin >> n;
    p = new int[n];
    for (int i = 0; i < n; ++i)
        std::cin >> p[i];
    std::sort(p, p + n);
    int x = std::upper_bound(p, p + n, 0) - p;
    if (x == 0)
    {
        int sum = 0;
        for (int i = 0; i < n; ++i)
            sum += p[i] * (n - i);
        std::cout << sum << '\n';
    }
    else if (x == n)
    {
        int sum = 0;
        for (int i = 0; i < n; ++i)
            sum -= p[i] * (i + 1);
        std::cout << sum << '\n';
    }
    else
    {
        for (int i = 0; i < 2; ++i)
        {
            f[i] = new int *[n];
            for (int j = 0; j < n; ++j)
            {
                f[i][j] = new int[n];
                for (int k = 0; k < n; ++k)
                    f[i][j][k] = INT_MAX;
            }
        }
        std::cout << std::min(dfs(x - 1, x - 1, false) - n * p[x - 1], dfs(x, x, false) + n * p[x]) << '\n';
    }
    return 0;
}