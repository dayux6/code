#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("CF1702G.in");
#endif
using std::cout;

int lg, *dep, **anc;
std::vector<int> *g;

void dfs(int x)
{
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

int getlca(int x, int y)
{
    if (dep[x] < dep[y])
        std::swap(x, y);
    while (dep[x] > dep[y])
        x = anc[x][(int)log2(dep[x] - dep[y])];
    if (x == y)
        return x;
    for (int i = lg; i >= 0; --i)
        if (anc[x][i] != anc[y][i])
        {
            x = anc[x][i];
            y = anc[y][i];
        }
    return anc[x][0];
}

int getanc(int x, int k)
{
    for (int i = 0; i <= lg; ++i)
        if ((k >> i) & 1)
            x = anc[x][i];
    return x;
}

int main()
{
    int n;
    cin >> n;
    g = new std::vector<int>[n + 1];
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    lg = log2(n);
    dep = new int[n + 1];
    dep[1] = 1;
    anc = new int *[n + 1];
    for (int i = 0; i <= n; ++i)
        anc[i] = new int[lg + 1]();
    dfs(1);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i)
    {
        int k;
        cin >> k;
        std::vector<int> vct;
        for (int j = 0; j < k; ++j)
        {
            int v;
            cin >> v;
            vct.emplace_back(v);
        }
        std::sort(vct.begin(), vct.end(), [=](int x, int y)
                  { return dep[x] > dep[y]; });
        int x = vct.front(), y;
        bool b = true;
        for (int v : vct)
            if (getanc(x, dep[x] - dep[v]) != v)
            {
                b = false;
                y = v;
                break;
            }
        if (b)
        {
            cout << "YES\n";
            continue;
        }
        int lca = getlca(x, y);
        for (int v : vct)
            if (!((v == lca || dep[v] > dep[lca]) && (getanc(x, dep[x] - dep[v]) == v || getanc(y, dep[y] - dep[v]) == v)))
            {
                b = true;
                break;
            }
        if (b)
            cout << "NO\n";
        else
            cout << "YES\n";
    }
    return 0;
}