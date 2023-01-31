#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("P3388.in");
#endif
using std::cout;

int dfc, *dfn, *low;
bool *cut;
std::vector<int> *g;

void tarjan(int x, bool isrt)
{
    ++dfc;
    dfn[x] = low[x] = dfc;
    int ch = 0;
    for (int v : g[x])
        if (!dfn[v])
        {
            ++ch;
            tarjan(v, false);
            low[x] = std::min(low[x], low[v]);
            if (!isrt && low[v] >= dfn[x])
                cut[x] = true;
        }
        else
            low[x] = std::min(low[x], dfn[v]);
    if (isrt && ch >= 2)
        cut[x] = true;
}

int main()
{
    int n, m;
    cin >> n >> m;
    g = new std::vector<int>[n + 1];
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    dfn = new int[n + 1]();
    low = new int[n + 1];
    cut = new bool[n + 1]();
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i, true);
    int cnt = 0;
    for (int x = 1; x <= n; ++x)
        if (cut[x])
            ++cnt;
    std::cout << cnt << std::endl;
    for (int x = 1; x <= n; ++x)
        if (cut[x])
            std::cout << x << ' ';
    std::cout << std::endl;
    return 0;
}