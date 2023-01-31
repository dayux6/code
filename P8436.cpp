#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("P8436.in");
#endif
using std::cout;

int ecnt, *hd, dfc, *dfn, *low;
bool *cut, *vis;
std::vector<std::vector<int>> dcc;

struct edge
{
    int v, nxt;

    edge() {}
    edge(int _v, int _nxt) : v(_v), nxt(_nxt) {}
} * e;

void addedge(int u, int v)
{
    e[ecnt] = edge(v, hd[u]);
    hd[u] = ecnt;
    ++ecnt;
}

void tarjan(int x, int pre)
{
    ++dfc;
    dfn[x] = low[x] = dfc;
    for (int i = hd[x]; ~i; i = e[i].nxt)
        if (!dfn[e[i].v])
        {
            tarjan(e[i].v, x);
            low[x] = std::min(low[x], low[e[i].v]);
            if (low[e[i].v] > dfn[x])
                cut[i] = cut[i ^ 1] = true;
        }
        else if (e[i].v ^ pre)
            low[x] = std::min(low[x], dfn[e[i].v]);
}

void dfs(int x)
{
    vis[x] = true;
    dcc.back().emplace_back(x);
    for (int i = hd[x]; ~i; i = e[i].nxt)
        if (!cut[i] && !vis[e[i].v])
            dfs(e[i].v);
}

int main()
{
    int n, m;
    cin >> n >> m;
    hd = new int[n + 1];
    std::fill_n(hd + 1, n, -1);
    e = new edge[m * 2];
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        addedge(u, v);
        addedge(v, u);
    }
    dfn = new int[n + 1]();
    low = new int[n + 1];
    cut = new bool[m * 2]();
    for (int x = 1; x <= n; ++x)
        if (!dfn[x])
            tarjan(x, 0);
    vis = new bool[n + 1]();
    for (int x = 1; x <= n; ++x)
        if (!vis[x])
        {
            dcc.emplace_back();
            dfs(x);
        }
    cout << dcc.size() << std::endl;
    for (std::vector<int> vct : dcc)
    {
        cout << vct.size() << ' ';
        for (int v : vct)
            cout << v << ' ';
        cout << std::endl;
    }
    return 0;
}