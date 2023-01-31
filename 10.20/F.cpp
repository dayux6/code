#include <bits/stdc++.h>

const int maxn = 1e5, maxlg = 16;

int n, dep[maxn + 1], anc[maxn + 1][maxlg + 1];
bool inq[maxn + 1];
long long d[maxn + 1];
std::unordered_map<int, std::array<long long, maxn + 1>> dis;

struct edge
{
    int v, w;

    edge(int _v, int _w) : v(_v), w(_w) {}
};
std::vector<edge> g[maxn + 1];

class DSU
{
private:
    int fa[maxn + 1];

    int find(int x)
    {
        while (x != fa[x])
            x = fa[x] = fa[fa[x]];
        return x;
    }

public:
    DSU(int n) { std::iota(fa + 1, fa + n + 1, 1); }

    void merge(int x, int y) { fa[find(x)] = find(y); }

    bool query(int x, int y) { return find(x) == find(y); }
};

void dfs(int x)
{
    for (int i = 1; i <= maxlg; ++i)
        anc[x][i] = anc[anc[x][i - 1]][i - 1];

    for (edge e : g[x])
        if (e.v != anc[x][0])
        {
            d[e.v] = d[x] + e.w;
            dep[e.v] = dep[x] + 1;
            anc[e.v][0] = x;
            dfs(e.v);
        }
}

int getlca(int x, int y)
{
    if (dep[x] < dep[y])
        std::swap(x, y);
    while (dep[x] > dep[y])
        x = anc[x][(int)std::log2(dep[x] - dep[y])];

    if (x == y)
        return x;
    for (int i = maxlg; i >= 0; --i)
        if (anc[x][i] != anc[y][i])
        {
            x = anc[x][i];
            y = anc[y][i];
        }

    return anc[x][0];
}

long long getdis(int x, int y) { return d[x] + d[y] - 2 * d[getlca(x, y)]; }

void spfa(int s)
{
    std::fill_n(dis[s].begin() + 1, n, LLONG_MAX);
    dis[s][s] = 0;
    std::fill_n(inq + 1, n, false);
    inq[s] = true;
    std::queue<int> q({s});

    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        inq[x] = false;

        for (edge e : g[x])
            if (dis[s][e.v] > dis[s][x] + e.w)
            {
                dis[s][e.v] = dis[s][x] + e.w;

                if (!inq[e.v])
                {
                    inq[e.v] = true;
                    q.push(e.v);
                }
            }
    }
}

int main()
{
    std::freopen("F.in", "r", stdin);

    int m;
    std::cin >> n >> m;

    std::unordered_set<int> ver;
    std::vector<std::tuple<int, int, int>> ve;
    DSU dsu(n);
    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        std::cin >> u >> v >> w;

        if (!dsu.query(u, v))
        {
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
            dsu.merge(u, v);
        }
        else
        {
            ver.emplace(u);
            ver.emplace(v);
            ve.emplace_back(u, v, w);
        }
    }

    dfs(1);

    for (std::tuple<int, int, int> t : ve)
    {
        g[std::get<0>(t)].emplace_back(std::get<1>(t), std::get<2>(t));
        g[std::get<1>(t)].emplace_back(std::get<0>(t), std::get<2>(t));
    }

    for (int s : ver)
        spfa(s);

    int q;
    std::cin >> q;
    for (int i = 0; i < q; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        long long min = getdis(u, v);
        for (int x : ver)
            min = std::min(min, dis[x][u] + dis[x][v]);

        std::cout << min << std::endl;
    }
    return 0;
}