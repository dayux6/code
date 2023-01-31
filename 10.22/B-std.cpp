#include <bits/stdc++.h>
using namespace std;
int n, dp[2][2110][2110], sum[101], ans = (1 << 30);
struct node
{
    int t, h;
} A[1010];
bool cmp(node A, node B)
{
    return A.h > B.h;
}
int main()
{
    std::freopen("book.in", "r", stdin);

    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d %d", &A[i].h, &A[i].t);
    memset(dp, 63, sizeof(dp));
    const int oo = dp[0][0][0];
    sort(A + 1, A + 1 + n, cmp);
    for (int i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + A[i].t;
    dp[0][0][0] = 0;
    for (int i = 1; i <= n; i++)
    {
        int now = i & 1, la = !now;
        memset(dp[now], 63, sizeof(dp[now]));
        for (int j = 0; j <= sum[i - 1]; j++)
        {
            for (int k = 0; k <= sum[i - 1]; k++)
            {
                int o = sum[i - 1] - j - k;
                if (o < 0)
                    continue;
                if (dp[la][j][k] == oo)
                    continue;
                if (j == 0)
                    dp[now][j + A[i].t][k] = min(dp[now][j + A[i].t][k], dp[la][j][k] + A[i].h);
                else
                    dp[now][j + A[i].t][k] = min(dp[now][j + A[i].t][k], dp[la][j][k]);
                if (k == 0)
                    dp[now][j][k + A[i].t] = min(dp[now][j][k + A[i].t], dp[la][j][k] + A[i].h);
                else
                    dp[now][j][k + A[i].t] = min(dp[now][j][k + A[i].t], dp[la][j][k]);
                if (o == 0)
                    dp[now][j][k] = min(dp[now][j][k], dp[la][j][k] + A[i].h);
                else
                    dp[now][j][k] = min(dp[now][j][k], dp[la][j][k]);
            }
        }
    }
    for (int i = 1; i <= sum[n]; i++)
    {
        for (int j = 1; j <= sum[n]; j++)
        {
            int o = sum[n] - i - j;
            if (o <= 0)
                continue;
            if (dp[n & 1][i][j] == oo)
                continue;
            std::cout << i << ' ' << j << ' ' << o << ' ' << max(max(i, j), o) * dp[n & 1][i][j] << std::endl;
            ans = min(ans, max(max(i, j), o) * dp[n & 1][i][j]);
        }
    }
    cout << ans << std::endl;
    return 0;
}