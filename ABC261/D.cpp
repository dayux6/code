#include <bits/stdc++.h>

int main()
{
    int n, m;
    std::cin >> n >> m;
    int *x = new int[n + 1];
    for (int i = 1; i <= n; ++i)
        std::cin >> x[i];
    std::unordered_map<int, int> map;
    for (int i = 0; i < m; ++i)
    {
        int c, y;
        std::cin >> c >> y;
        map.emplace(c, y);
    }
    long long **f = new long long *[n + 1];
    for (int i = 0; i <= n; ++i)
        f[i] = new long long[n + 1]();
    for (int i = 1; i <= n; ++i)
    {
        f[i][0] = std::max(f[i][0], f[i - 1][0]);
        for (int j = 1; j <= i; ++j)
        {
            if (j != i)
                f[i][0] = std::max(f[i][0], f[i - 1][j]);
            f[i][j] = f[i - 1][j - 1] + x[i] + map[j];
        }
        f[i][0] += map[0];
    }
    long long max = 0;
    for (int i = 0; i <= n; ++i)
        max = std::max(max, f[n][i]);
    std::cout << max << std::endl;
    return 0;
}