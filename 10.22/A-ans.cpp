#include <bits/stdc++.h>

void read(int &x)
{
    x = 0;
    char c = std::getchar();

    while (!std::isdigit(c))
        c = std::getchar();
    while (std::isdigit(c))
    {
        x = x * 10 + (c ^ 48);
        c = std::getchar();
    }
}

const int maxn = 1e3, maxlg = 10;

int s[maxn + 1][maxn + 1], sum[maxn + 1][maxn + 1];
std::deque<int> q[maxn + 1];

int main()
{
    std::freopen("trip.in", "r", stdin);
    std::freopen("trip.out", "w", stdout);

    int n, m, a, b, c, d;
    read(m);
    read(n);
    read(b);
    read(a);
    read(d);
    read(c);

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            read(s[i][j]);
            s[i][j] += s[i][j - 1];
        }

        for (int j = 1; j <= m; ++j)
            s[i][j] += s[i - 1][j];
    }

    auto calc = [&](int x1, int y1, int x2, int y2)
    { return s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + s[x1 - 1][y1 - 1]; };

    for (int i = c; i <= n; ++i)
        for (int j = d; j <= m; ++j)
            sum[i][j] = calc(i - c + 1, j - d + 1, i, j);

    for (int i = c; i < a; ++i)
        for (int j = d; j <= m; ++j)
        {
            while (!q[j].empty() && sum[i][j] <= sum[q[j].back()][j])
                q[j].pop_back();
            q[j].push_back(i);
        }

    int ans = 0;
    for (int i = a; i <= n; ++i)
    {
        for (int j = d; j <= m; ++j)
            while (!q[j].empty() && q[j].front() <= i - a + c)
                q[j].pop_front();

        std::deque<int> dq;
        for (int j = d; j < b; ++j)
        {
            while (!dq.empty() && sum[q[j].front()][j] <= sum[q[dq.back()].front()][dq.back()])
                dq.pop_back();
            dq.push_back(j);
        }

        for (int j = b; j <= m; ++j)
        {
            while (!dq.empty() && dq.front() <= j - b + d)
                dq.pop_front();
            ans = std::max(ans, calc(i - a + 1, j - b + 1, i, j) - sum[q[dq.front()].front()][dq.front()]);

            while (!dq.empty() && sum[q[j].front()][j] <= sum[q[dq.back()].front()][dq.back()])
                dq.pop_back();
            dq.push_back(j);
        }

        for (int j = d; j <= m; ++j)
        {
            while (!q[j].empty() && sum[i][j] <= sum[q[j].back()][j])
                q[j].pop_back();
            q[j].push_back(i);
        }
    }

    std::cout << ans << std::endl;
    return 0;
}