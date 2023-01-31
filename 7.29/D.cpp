#include <bits/stdc++.h>

const int maxn = 1e5;

int col[maxn + 1], ind[maxn + 1], dis[maxn + 1];
bool vis[maxn + 1];
std::vector<int> scc[maxn + 1];

struct edge
{
    int v, w;

    edge(int _v, int _w) : v(_v), w(_w) {}
};

std::vector<edge> g[maxn + 1], dag[maxn + 1];

void dfs(int x, int c)
{
    col[x] = c;
    scc[c].emplace_back(x);
    for (edge e : g[x])
        if (col[e.v] ^ c)
            dfs(e.v, c);
}

int main()
{
    freopen("D.in", "r", stdin);
    int n, m1, m2, s;
    std::cin >> n >> m1 >> m2 >> s;
    for (int i = 0; i < m1; ++i)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    int cnt = 0;
    for (int i = 1; i <= n; ++i)
        if (!col[i])
        {
            ++cnt;
            dfs(i, cnt);
        }
    for (int i = 0; i < m2; ++i)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        ++ind[col[v]];
        dag[u].emplace_back(v, w);
    }
    std::queue<int> q;
    for (int i = 1; i <= cnt; ++i)
        if (!ind[i])
            q.emplace(i);
    std::fill_n(dis + 1, n, INT_MAX);
    dis[s] = 0;
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        std::priority_queue<std::pair<int, int>> heap;
        for (int v : scc[x])
            if (dis[v] ^ INT_MAX)
                heap.emplace(-dis[v], v);
        while (!heap.empty())
        {
            int v = heap.top().second;
            heap.pop();
            if (!vis[v])
            {
                vis[v] = true;
                for (edge e : g[v])
                    if (dis[e.v] > dis[v] + e.w)
                    {
                        dis[e.v] = dis[v] + e.w;
                        if (!vis[e.v])
                            heap.emplace(-dis[e.v], e.v);
                    }
            }
        }
        for (int v : scc[x])
            for (edge e : dag[v])
            {
                if (dis[v] ^ INT_MAX)
                    dis[e.v] = std::min(dis[e.v], dis[v] + e.w);
                --ind[col[e.v]];
                if (!ind[col[e.v]])
                    q.emplace(col[e.v]);
            }
    }
    for (int i = 1; i <= n; ++i)
        if (dis[i] ^ INT_MAX)
            std::cout << dis[i] << std::endl;
        else
            std::cout << "NO PATH" << std::endl;
    return 0;
}