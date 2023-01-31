#include <bits/stdc++.h>

int n, m, *cnt[3];

int dfs(int d, int c, int s)
{
    if (d == n - 1)
        return s + m - cnt[2][d];
    int min = INT_MAX;
    if (c == 0 && d != n - 2)
        min = std::min(min, dfs(d + 1, 0, s + m - cnt[0][d]));
    if (c == 0)
        min = std::min(min, dfs(d + 1, 1, s + m - cnt[1][d]));
    if (c == 1)
        min = std::min(min, std::min(dfs(d + 1, 1, s + m - cnt[1][d]), dfs(d + 1, 2, s + m - cnt[2][d])));
    if (c == 2)
        min = std::min(min, dfs(d + 1, 2, s + m - cnt[2][d]));
    return min;
}

int main()
{
    freopen("A.in", "r", stdin);
    std::cin >> n >> m;
    for (int i = 0; i < 3; ++i)
        cnt[i] = new int[n]();
    for (int i = 0; i < n; ++i)
    {
        std::string s;
        std::cin >> s;
        for (int j = 0; j < m; ++j)
            switch (s.at(j))
            {
            case 'W':
                cnt[0][i]++;
                break;
            case 'B':
                cnt[1][i]++;
                break;
            case 'R':
                cnt[2][i]++;
                break;
            }
    }
    std::cout << dfs(1, 0, m - cnt[0][0]) << '\n';
    return 0;
}