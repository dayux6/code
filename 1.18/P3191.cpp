#include <bits/stdc++.h>

const int maxn = 20, dx[] = {-1, 0, 0, 1}, dy[] = {0, -1, 1, 0};

int n, m, s, t, h[maxn * maxn * (maxn * maxn + 1) + 2], cur[maxn * maxn * (maxn * maxn + 1) + 2], dep[maxn * maxn * (maxn * maxn + 1) + 1], dis[maxn * maxn][maxn + 1][maxn + 1];
char str[maxn + 1][maxn + 1];
std::vector<std::pair<int, int>> vd;

struct edge
{
    int v, w, p;

    edge(int _v, int _w, int _p)
    {
        v = _v;
        w = _w;
        p = _p;
    }
};
std::vector<edge> e;

void addedge(int u, int v, int w)
{
    e.emplace_back(v, w, h[u]);
    h[u] = e.size() - 1;
}

void add(int u, int v, int w)
{
    addedge(u, v, w);
    addedge(v, u, 0);
}

void getdis(int id)
{
    std::queue<std::pair<int, int>> q;
    q.emplace(vd[id]);

    while (!q.empty())
    {
        std::pair<int, int> pr = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i)
        {
            int nx = pr.first + dx[i], ny = pr.second + dy[i];

            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && str[nx][ny] == '.' && dis[id][nx][ny] == 0)
            {
                dis[id][nx][ny] = dis[id][pr.first][pr.second] + 1;
                q.emplace(nx, ny);
            }
        }
    }
}

bool bfs()
{
    std::memcpy(cur, h, sizeof(h));
    std::memset(dep, -1, sizeof(dep));

    dep[0] = 0;
    std::queue<int> q;
    q.emplace(0);
    while (!q.empty())
    {
        int x = q.front();
        q.pop();

        for (int i = h[x]; i != -1; i = e[i].p)
            if (e[i].w != 0 && dep[e[i].v] == -1)
            {
                dep[e[i].v] = dep[x] + 1;
                q.emplace(e[i].v);
            }
    }

    return dep[t] != -1;
}

int dfs(int x, int f)
{
    if (x == t || f == 0)
        return f;

    int res = f;
    for (int &i = cur[x]; i != -1; i = e[i].p)
        if (dep[e[i].v] == dep[x] + 1)
        {
            int tmp = dfs(e[i].v, std::min(res, e[i].w));
            res -= tmp;
            e[i].w -= tmp;
            e[i ^ 1].w += tmp;
            if (res == 0)
                return f;
        }

    return f - res;
}

int dinic()
{
    int ret = 0;
    while (bfs())
        ret += dfs(s, INT_MAX);
    return ret;
}

int main()
{
    std::freopen("P3191.in", "r", stdin);
    std::freopen("P3191.err", "w", stderr);

    std::cin >> n >> m;

    auto id = [&](int x, int y)
    { return (x - 1) * m + y; };

    for (int i = 1; i <= n; ++i)
    {
        std::scanf("%s", str[i] + 1);

        for (int j = 1; j <= m; ++j)
            if (str[i][j] == 'D')
                vd.emplace_back(i, j);
    }

    for (std::size_t i = 0; i < vd.size(); ++i)
        getdis(i);

    s = 0;
    t = n * m * (vd.size() + 1) + 1;
    int l = 0, r = n * m, ans = -1;

    while (l <= r)
    {
        int mid = (l + r) / 2;

        std::memset(h, -1, sizeof(h));
        std::vector<edge>().swap(e);

        int cnt = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                if (str[i][j] == '.')
                {
                    ++cnt;
                    add(s, id(i, j), 1);

                    for (std::size_t k = 0; k < vd.size(); ++k)
                        if (dis[k][i][j] != 0 && dis[k][i][j] <= mid)
                            add(id(i, j), n * m + k * mid + dis[k][i][j], 1);
                }

        for (std::size_t i = 0; i < vd.size(); ++i)
        {
            for (int j = 1; j <= mid; ++j)
                add(n * m + i * mid + j, t, 1);
            for (int j = 1; j < mid; ++j)
                add(n * m + i * mid + j, n * m + i * mid + j + 1, INT_MAX);
        }

        if (dinic() == cnt)
        {
            r = mid - 1;
            ans = mid;
        }
        else
            l = mid + 1;
    }

    if (ans == -1)
        std::puts("impossible");
    else
        std::cout << ans << std::endl;
    return 0;
}