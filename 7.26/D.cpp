#include <bits/stdc++.h>

const int maxn = 1e5, maxm = 5e5, maxq = 1e5, maxlg = 16;

struct edge
{
    int v, w;

    edge(int _v, int _w) : v(_v), w(_w) {}
};

struct query
{
    int no, x, y;

    query(int _no, int _x, int _y) : no(_no), x(_x), y(_y) {}
};

int lg, dep[maxn + 1], anc[maxn + 1][maxlg + 1];
long long dis[maxn + 1], ans[maxq + 1];
bool vis[maxn + 1];
std::vector<int> t[maxn + 1];
std::vector<edge> g[maxn + 1];
std::vector<query> vq[maxn + 1];
std::tuple<int, int, int> e[maxm];

void dfs(int x)
{
    for (int i = 1; i <= lg; ++i)
        anc[x][i] = anc[anc[x][i - 1]][i - 1];
    for (int v : t[x])
        if (v ^ anc[x][0])
        {
            dep[v] = dep[x] + 1;
            anc[v][0] = x;
            dfs(v);
        }
}

int getlca(int x, int y)
{
    if (dep[x] < dep[y])
        std::swap(x, y);
    while (dep[x] > dep[y])
        x = anc[x][(int)log2(dep[x] - dep[y])];
    if (x == y)
        return x;
    for (int i = lg; i >= 0; --i)
        if (anc[x][i] ^ anc[y][i])
        {
            x = anc[x][i];
            y = anc[y][i];
        }
    return anc[x][0];
}

void dijkstra(int s)
{
    dis[s] = 0;
    std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<std::pair<long long, int>>> q;
    q.emplace(dis[s], s);
    while (!q.empty())
    {
        int x = q.top().second;
        q.pop();
        if (!vis[x])
        {
            vis[x] = true;
            for (edge E : g[x])
                if (dis[E.v] > dis[x] + E.w)
                {
                    dis[E.v] = dis[x] + E.w;
                    if (!vis[E.v])
                        q.emplace(dis[E.v], E.v);
                }
        }
    }
}

void clear(int x)
{
    dis[x] = LLONG_MAX;
    vis[x] = false;
    for (int v : t[x])
        if (v ^ anc[x][0])
            clear(v);
}

void getans(int x)
{
    for (int v : t[x])
        if (v ^ anc[x][0])
        {
            getans(v);
            clear(v);
            for (query q : vq[v])
                vq[x].emplace_back(q);
        }
    for (edge E : g[x])
        g[E.v].emplace_back(x, E.w);
    if (!vq[x].empty())
    {
        dijkstra(x);
        for (query q : vq[x])
            ans[q.no] = std::min(ans[q.no], dis[q.x] + dis[q.y]);
    }
}

int main()
{
    freopen("D.in", "r", stdin);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, m, q;
    std::cin >> n >> m >> q;
    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        e[i] = std::tie(u, v, w);
    }
    for (int i = 0; i < n - 1; ++i)
    {
        t[std::get<0>(e[i])].emplace_back(std::get<1>(e[i]));
        t[std::get<1>(e[i])].emplace_back(std::get<0>(e[i]));
    }
    lg = log2(n);
    dfs(1);
    for (int i = 0; i < q; ++i)
    {
        ans[i] = LLONG_MAX;
        int u, v;
        std::cin >> u >> v;
        vq[getlca(u, v)].emplace_back(i, u, v);
    }
    for (int i = 0; i < m; ++i)
    {
        int u = std::get<0>(e[i]), v = std::get<1>(e[i]);
        if (dep[u] > dep[v])
            std::swap(u, v);
        g[u].emplace_back(v, std::get<2>(e[i]));
    }
    getans(1);
    for (int i = 0; i < q; ++i)
        std::cout << ans[i] << std::endl;
    return 0;
}