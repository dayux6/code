#include <bits/stdc++.h>

const int maxn = 500;

int r[maxn + 1][maxn + 1][4], s[maxn + 1][maxn + 1][maxn / 2 + 1];
char str[maxn + 1];

int main()
{
    freopen("C.in", "r", stdin);
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", str + 1);
        for (int j = 1; j <= m; ++j)
            switch (str[j])
            {
            case 'B':
                r[i][j][0] = std::min({r[i - 1][j][0], r[i][j - 1][0], r[i - 1][j - 1][0]}) + 1;
                break;
            case 'W':
                r[i][j][1] = std::min({r[i - 1][j][1], r[i][j - 1][1], r[i - 1][j - 1][1]}) + 1;
                break;
            case 'P':
                r[i][j][2] = std::min({r[i - 1][j][2], r[i][j - 1][2], r[i - 1][j - 1][2]}) + 1;
                break;
            case 'G':
                r[i][j][3] = std::min({r[i - 1][j][3], r[i][j - 1][3], r[i - 1][j - 1][3]}) + 1;
                break;
            }
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            for (int k = 1; k <= std::min(i, j) / 2; ++k)
                s[i][j][k] = s[i - 1][j][k] + s[i][j - 1][k] - s[i - 1][j - 1][k] + (r[i][j][3] == k && r[i][j - k][2] == k && r[i - k][j][1] == k && r[i - k][j - k][0] >= k);
    for (int i = 0; i < q; ++i)
    {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        int l = 1, r = std::min(x2 - x1 + 1, y2 - y1 + 1) / 2, ans = 0;
        while (l <= r)
        {
            int mid = (l + r) / 2;
            if (s[x2][y2][mid] - s[x1 + mid * 2 - 2][y2][mid] - s[x2][y1 + mid * 2 - 2][mid] + s[x1 + mid * 2 - 2][y1 + mid * 2 - 2][mid] > 0)
            {
                l = mid + 1;
                ans = mid * mid * 4;
            }
            else
                r = mid - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}