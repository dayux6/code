#include <bits/stdc++.h>

const int maxn = 1e5, maxlg = 16;

int dfc, dfn[maxn + 1], dep[maxn + 1], lg, anc[maxn + 1][maxlg + 1], f[maxn + 1];
bool b[maxn + 1];
std::vector<int> g[maxn + 1], vt[maxn + 1];

void dfs(int x)
{
    ++dfc;
    dfn[x] = dfc;

    for (int i = 1; i <= lg; ++i)
        anc[x][i] = anc[anc[x][i - 1]][i - 1];

    for (int v : g[x])
        if (v != anc[x][0])
        {
            dep[v] = dep[x] + 1;
            anc[v][0] = x;
            dfs(v);
        }
}

void build()
{
}

void dp1(int x)
{
}

void dp2(int x)
{
}

int main()
{
    int n, q;
    std::cin >> n >> q;

    for (int i = 1; i < n; ++i)
    {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    return 0;
}