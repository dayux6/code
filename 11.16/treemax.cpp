#include <bits/stdc++.h>

const int maxn = 4e3;

int n, k, a[maxn + 1], u[maxn], v[maxn], w[maxn], fa[maxn + 1], dep[maxn + 1];
long long ans;
bool vis[maxn + 1];
std::vector<int> g[maxn + 1], cur;

void init(int x)
{
    for (int v : g[x])
        if (v != fa[x])
        {
            fa[v] = x;
            dep[v] = dep[x] + 1;
            init(v);
        }
}

void jump(int x, int y)
{
    if (dep[x] < dep[y])
        std::swap(x, y);

    vis[x] = vis[y] = true;
    while (dep[x] > dep[y])
    {
        x = fa[x];
        vis[x] = true;
    }

    if (x == y)
        return;

    while (x != y)
    {
        x = fa[x];
        vis[x] = true;
        y = fa[y];
        vis[y] = true;
    }
}

void dfs(int d)
{
    std::fill_n(vis + 1, n, false);
    for (std::size_t i = 0; i < d; ++i)
        for (std::size_t j = 0; j < i; ++j)
            jump(cur[i], cur[j]);

    long long s = 0;
    for (int i = 1; i < n; ++i)
        if (vis[u[i]] && vis[v[i]])
            s += w[i];
    ans = std::max(ans, s);

    if (d == k)
        return;

    for (int i = cur.empty() ? 1 : (cur.back() + 1); i <= n; ++i)
    {
        bool flg = true;
        for (int x : cur)
            if (a[i] == a[x])
            {
                flg = false;
                break;
            }

        if (flg)
        {
            cur.emplace_back(i);
            dfs(d + 1);
            cur.pop_back();
        }
    }
}

int main()
{
    std::freopen("treemax.in", "r", stdin);
    std::freopen("treemax.out", "w", stdout);

    std::cin >> n >> k;

    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];

    for (int i = 1; i < n; ++i)
    {
        std::cin >> u[i] >> v[i] >> w[i];
        g[u[i]].emplace_back(v[i]);
        g[v[i]].emplace_back(u[i]);
    }

    init(1);
    dfs(0);

    std::cout << ans << std::endl;
    return 0;
}