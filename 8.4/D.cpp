#include <bits/stdc++.h>

const int maxn = 5e5, maxlg = 18;

int fa[maxn + 1], c[maxn + 1], dep[maxn + 1], f[maxn + 1][maxlg + 1];
std::vector<int> g[maxn + 1];

struct point
{
    int x, y;

    point(int _x) : x(dep[_x]), y(c[_x]) {}
};

struct vec
{
    int x, y;

    vec(point _x, point _y) : x(_x.x - _y.x), y(_x.y - _y.y) {}
};

long long cross(vec x, vec y) { return 1ll * x.x * y.y - 1ll * x.y * y.x; }

void dfs(int x)
{
    int cur = fa[x];
    if (cur && f[cur][0] && cross(vec(point(cur), point(f[cur][0])), vec(point(x), point(f[cur][0]))) <= 0)
    {
        for (int i = log2(dep[cur] - 1); i >= 0 && dep[cur] > 1; --i)
            if (f[cur][i] && f[f[cur][i]][0] && cross(vec(point(f[cur][i]), point(f[f[cur][i]][0])), vec(point(x), point(f[f[cur][i]][0]))) <= 0)
                cur = f[cur][i];
        f[x][0] = f[cur][0];
    }
    else
        f[x][0] = cur;

    for (int i = 1; i <= log2(dep[x] - 1); ++i)
        f[x][i] = f[f[x][i - 1]][i - 1];

    for (int v : g[x])
    {
        dep[v] = dep[x] + 1;
        dfs(v);
    }
}

int main()
{
    freopen("D.in", "r", stdin);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
        std::cin >> c[i];
    for (int i = 2; i <= n; ++i)
    {
        std::cin >> fa[i];
        g[fa[i]].push_back(i);
    }

    dep[1] = 1;
    dfs(1);

    std::cout << std::fixed << std::setprecision(9);
    for (int i = 2; i <= n; ++i)
        std::cout << -1.0 * (c[i] - c[f[i][0]]) / (dep[i] - dep[f[i][0]]) << std::endl;
    return 0;
}