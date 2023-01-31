#include <bits/stdc++.h>

const int maxn = 500, dx[] = {1, 0, 0, -1}, dy[] = {0, -1, 1, 0};
const char dc[] = {'D', 'L', 'R', 'U'};

int n, m, dis[maxn + 1][maxn + 1][4], pre[maxn + 1][maxn + 1][4];
bool inq[maxn + 1][maxn + 1][4];
char c[maxn + 1][maxn + 1];

struct node
{
    int x, y, d;

    node() {}
    node(int _x, int _y, int _d) : x(_x), y(_y), d(_d) {}
};

void dfs(int x, int y, int pre)
{
    if (x == n && y == m)
        return;

    int min = INT_MAX;
    for (int i = 0; i < 4; ++i)
        min = std::min(min, dis[x][y][i] + (i != pre));

    for (int i = 0; i < 4; ++i)
        if (dis[x][y][i] + (i != pre) == min)
        {
            putchar(dc[i]);
            dfs(x + dx[i], y + dy[i], i);
            break;
        }
};

int main()
{
    std::freopen("run.in", "r", stdin);
    std::freopen("run.out", "w", stdout);

    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        std::scanf("%s", c[i] + 1);

    inq[n][m][0] = inq[n][m][1] = inq[n][m][2] = inq[n][m][3] = true;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            for (int k = 0; k < 4; ++k)
                dis[i][j][k] = INT_MAX / 2;
    dis[n][m][0] = dis[n][m][1] = dis[n][m][2] = dis[n][m][3] = 0;
    std::queue<node> q({node(n, m, 0), node(n, m, 1), node(n, m, 2), node(n, m, 3)});
    while (!q.empty())
    {
        node x = q.front();
        q.pop();
        inq[x.x][x.y][x.d] = false;

        for (int i = 0; i < 4; ++i)
        {
            node nx(x.x - dx[i], x.y - dy[i], i);

            if (nx.x >= 1 && nx.x <= n && nx.y >= 1 && nx.y <= m && dc[i] != c[nx.x][nx.y] && c[nx.x][nx.y] != 'S')
            {
                int min = dis[x.x][x.y][x.d] + (x.d != i);

                if (min < dis[nx.x][nx.y][i])
                {
                    dis[nx.x][nx.y][i] = min;
                    pre[nx.x][nx.y][i] = x.d;

                    if (!inq[nx.x][nx.y][i])
                    {
                        q.emplace(nx);
                        inq[nx.x][nx.y][i] = true;
                    }
                }
            }
        }
    }

    int min = INT_MAX / 2, pre;
    for (int i = 0; i < 4; ++i)
        if (dis[1][1][i] < min)
        {
            min = dis[1][1][i];
            pre = i;
        }

    if (min == INT_MAX / 2)
        std::puts("No Solution");
    else
    {
        std::printf("%d\n", min);
        dfs(1, 1, pre);
    }
    return 0;
}