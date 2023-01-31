#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("P3387.in");
#endif
using std::cout;

int *val, dfc, *dfn, *low, scc, *bel, *sum;
bool *ins;
std::vector<int> *g, *ng;
std::stack<int> s;

void tarjan(int x)
{
    ++dfc;
    dfn[x] = low[x] = dfc;
    s.emplace(x);
    ins[x] = true;
    for (int v : g[x])
        if (dfn[v] == 0)
        {
            tarjan(v);
            low[x] = std::min(low[x], low[v]);
        }
        else if (ins[v])
            low[x] = std::min(low[x], dfn[v]);
    if (dfn[x] == low[x])
    {
        ++scc;
        while (!s.empty())
        {
            int v = s.top();
            s.pop();
            ins[v] = false;
            bel[v] = scc;
            if (v == x)
                break;
        }
    }
}

int topo()
{
    int *ind = new int[scc + 1]();
    for (int x = 1; x <= scc; ++x)
        for (int v : ng[x])
            ++ind[v];
    int *f = new int[scc + 1];
    std::queue<int> q;
    for (int x = 1; x <= scc; ++x)
        if (!ind[x])
        {
            f[x] = sum[x];
            q.emplace(x);
        }
        else
            f[x] = 0;
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        for (int v : ng[x])
        {
            --ind[v];
            f[v] = std::max(f[v], f[x] + sum[v]);
            if (!ind[v])
                q.emplace(v);
        }
    }
    int max = 0;
    for (int x = 1; x <= scc; ++x)
        max = std::max(max, f[x]);
    return max;
}

int main()
{
    int n, m;
    cin >> n >> m;
    val = new int[n + 1];
    for (int i = 1; i <= n; ++i)
        cin >> val[i];
    g = new std::vector<int>[n + 1];
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        g[u].emplace_back(v);
    }
    dfn = new int[n + 1]();
    low = new int[n + 1];
    bel = new int[n + 1];
    ins = new bool[n + 1]();
    for (int x = 1; x <= n; ++x)
        if (!dfn[x])
            tarjan(x);
    sum = new int[scc + 1]();
    ng = new std::vector<int>[scc + 1];
    for (int x = 1; x <= n; ++x)
    {
        sum[bel[x]] += val[x];
        for (int v : g[x])
            if (bel[x] ^ bel[v])
                ng[bel[x]].emplace_back(bel[v]);
    }
    for (int x = 1; x <= scc; ++x)
    {
        std::sort(ng[x].begin(), ng[x].end());
        ng[x].erase(std::unique(ng[x].begin(), ng[x].end()), ng[x].end());
    }
    cout << topo() << std::endl;
    return 0;
}