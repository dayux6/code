#include <bits/stdc++.h>

const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};

int main()
{
    freopen("B.in", "r", stdin);
    int n, s;
    std::cin >> n >> s;
    int sx, sy, ex, ey, **b = new int *[n], **d = new int *[n];
    char **c = new char *[n];
    std::queue<std::pair<int, int>> bee;
    for (int i = 0; i < n; ++i)
    {
        b[i] = new int[n];
        std::fill_n(b[i], n, INT_MAX);
        d[i] = new int[n];
        c[i] = new char[n];
        for (int j = 0; j < n; ++j)
        {
            std::cin >> c[i][j];
            switch (c[i][j])
            {
            case 'M':
            {
                sx = i;
                sy = j;
                c[i][j] = 'G';
                break;
            }
            case 'D':
            {
                ex = i;
                ey = j;
                break;
            }
            case 'H':
            {
                b[i][j] = 0;
                bee.emplace(i, j);
                break;
            }
            }
        }
    }
    while (!bee.empty())
    {
        std::pair<int, int> pr = bee.front();
        bee.pop();
        for (int i = 0; i < 4; ++i)
        {
            int nx = pr.first + dx[i], ny = pr.second + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && c[nx][ny] == 'G' && b[nx][ny] == INT_MAX)
            {
                b[nx][ny] = b[pr.first][pr.second] + s;
                bee.emplace(nx, ny);
            }
        }
    }
    int l = 0, r = b[sx][sy] - s, ans = -1;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        for (int i = 0; i < n; ++i)
            std::fill_n(d[i], n, INT_MAX);
        d[sx][sy] = mid;
        std::queue<std::pair<int, int>> q;
        q.emplace(sx, sy);
        while (!q.empty())
        {
            std::pair<int, int> pr = q.front();
            q.pop();
            for (int i = 0; i < 4; ++i)
            {
                int nx = pr.first + dx[i], ny = pr.second + dy[i];
                if (nx >= 0 && nx < n && ny >= 0 && ny < n && (c[nx][ny] == 'G' || c[nx][ny] == 'D') && d[nx][ny] == INT_MAX && d[pr.first][pr.second] + 1 < b[nx][ny])
                {
                    d[nx][ny] = d[pr.first][pr.second] + 1;
                    q.emplace(nx, ny);
                }
            }
        }
        if (d[ex][ey] != INT_MAX)
        {
            l = mid + 1;
            ans = mid / s;
        }
        else
            r = mid - 1;
    }
    std::cout << ans << std::endl;
    return 0;
}