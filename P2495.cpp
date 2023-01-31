#include <bits/stdc++.h>

const int maxn = 2.5e5, maxlg = 17;

int dfc, dfn[maxn + 1], dep[maxn + 1], lg, anc[maxn + 1][maxlg + 1], min[maxn + 1][maxlg + 1];
bool b[maxn + 1];

struct edge
{
    int v, w;

    edge(int _v, int _w) : v(_v), w(_w) {}
};
std::vector<edge> t[maxn + 1], vt[maxn + 1];

void dfs(int x)
{
    ++dfc;
    dfn[x] = dfc;
    if (dep[x])
        for (int i = 1; i <= log2(dep[x]); ++i)
        {
            anc[x][i] = anc[anc[x][i - 1]][i - 1];
            min[x][i] = std::min(min[x][i - 1], min[anc[x][i - 1]][i - 1]);
        }
    for (edge e : t[x])
        if (e.v ^ anc[x][0])
        {
            dep[e.v] = dep[x] + 1;
            anc[e.v][0] = x;
            min[e.v][0] = e.w;
            dfs(e.v);
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

int getmin(int x, int y)
{
    int k = dep[x] - dep[y], ret = INT_MAX;
    for (int i = 0; i <= log2(k); ++i)
        if ((k >> i) & 1)
        {
            ret = std::min(ret, min[x][i]);
            x = anc[x][i];
        }
    return ret;
}

long long dp(int x)
{
    long long ret = 0;
    for (edge e : vt[x])
    {
        long long tmp = dp(e.v);
        if (b[e.v])
            ret += e.w;
        else
            ret += std::min((long long)e.w, tmp);
    }
    return ret;
}

int main()
{
    freopen("P2495.in", "r", stdin);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        t[u].emplace_back(v, w);
        t[v].emplace_back(u, w);
    }
    lg = log2(n);
    for (int i = 0; i <= n; ++i)
        std::fill_n(min[i], lg + 1, INT_MAX);
    dfs(1);
    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i)
    {
        int k;
        std::cin >> k;
        std::vector<int> vct;
        for (int j = 0; j < k; ++j)
        {
            int x;
            std::cin >> x;
            b[x] = true;
            vct.emplace_back(x);
        }
        std::sort(vct.begin(), vct.end(), [=](int x, int y)
                  { return dfn[x] < dfn[y]; });
        std::vector<int> s({1}), used({1});
        for (int v : vct)
            if (v ^ 1)
            {
                int lca = getlca(v, s.back());
                if (lca ^ s.back())
                {
                    while (dfn[s.at(s.size() - 2)] > dfn[lca])
                    {
                        vt[s.at(s.size() - 2)].emplace_back(s.back(), getmin(s.back(), s.at(s.size() - 2)));
                        s.pop_back();
                    }
                    if (dfn[s.at(s.size() - 2)] ^ dfn[lca])
                    {
                        vt[lca].emplace_back(s.back(), getmin(s.back(), lca));
                        s.back() = lca;
                        used.emplace_back(lca);
                    }
                    else
                    {
                        vt[s.at(s.size() - 2)].emplace_back(s.back(), getmin(s.back(), s.at(s.size() - 2)));
                        s.pop_back();
                    }
                }
                s.emplace_back(v);
                used.emplace_back(v);
            }
        for (int i = 1; i < s.size(); ++i)
            vt[s.at(i - 1)].emplace_back(s.at(i), getmin(s.at(i), s.at(i - 1)));
        std::cout << dp(1) << std::endl;
        for (int v : vct)
            b[v] = false;
        for (int v : used)
            vt[v].clear();
    }
    return 0;
}