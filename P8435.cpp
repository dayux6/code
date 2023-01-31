#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("P8435.in");
#endif
using std::cout;

int dfc, *dfn, *low;
std::vector<int> *g;
std::vector<std::vector<int>> dcc;
std::stack<int> s;

void tarjan(int x, bool isrt)
{
    ++dfc;
    dfn[x] = low[x] = dfc;
    s.push(x);
    int ch = 0;
    for (int v : g[x])
        if (!dfn[v])
        {
            ++ch;
            tarjan(v, false);
            low[x] = std::min(low[x], low[v]);
            if (low[v] >= dfn[x])
            {
                dcc.emplace_back(std::vector<int>{x});
                while (!s.empty())
                {
                    int y = s.top();
                    s.pop();
                    dcc.back().emplace_back(y);
                    if (y == v)
                        break;
                }
            }
        }
        else
            low[x] = std::min(low[x], dfn[v]);
    if (isrt && !ch)
        dcc.emplace_back(std::vector<int>({x}));
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    g = new std::vector<int>[n + 1];
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        if (u ^ v)
        {
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
    }
    dfn = new int[n + 1]();
    low = new int[n + 1];
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i, true);
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