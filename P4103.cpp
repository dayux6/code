#include <bits/stdc++.h>

const int maxn = 1e6, maxlg = 19;

int dfc, dfn[maxn + 1], dep[maxn + 1], anc[maxn + 1][maxlg + 1], k, res2, res3, cnt[maxn + 1], min[maxn + 1], max[maxn + 1];
long long res1;
bool b[maxn + 1];
std::vector<int> g[maxn + 1];

struct edge
{
    int v, w;

    edge(int _v, int _w) : v(_v), w(_w) {}
};
std::vector<edge> vt[maxn + 1];

void dfs(int x)
{
    ++dfc;
    dfn[x] = dfc;

    int lim = log2(dep[x]);
    for (int i = 1; i <= lim; ++i)
        anc[x][i] = anc[anc[x][i - 1]][i - 1];

    for (int v : g[x])
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

    for (int i = log2(dep[x]); i >= 0; --i)
        if (anc[x][i] ^ anc[y][i])
        {
            x = anc[x][i];
            y = anc[y][i];
        }
    return anc[x][0];
}

void dp(int x)
{
    if (b[x])
    {
        cnt[x] = 1;
        min[x] = max[x] = 0;
    }

    for (edge e : vt[x])
    {
        dp(e.v);

        cnt[x] += cnt[e.v];
        if (cnt[x])
        {
            res2 = std::min(res2, min[x] + min[e.v] + e.w);
            min[x] = std::min(min[x], min[e.v] + e.w);
            res3 = std::max(res3, max[x] + max[e.v] + e.w);
            max[x] = std::max(max[x], max[e.v] + e.w);
        }
    }

    for (edge e : vt[x])
        res1 += 1ll * cnt[e.v] * (k - cnt[e.v]) * e.w;
}

int main()
{
    freopen("P4103.in", "r", stdin);
    int n;
    std::cin >> n;

    for (int i = 1; i < n; ++i)
    {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dep[1] = 1;
    dfs(1);

    int q;
    std::cin >> q;
    for (int i = 0; i < q; ++i)
    {
        std::cin >> k;

        std::vector<int> vct;
        for (int j = 0; j < k; ++j)
        {
            int x;
            std::cin >> x;
            b[x] = true;
            vct.push_back(x);
        }
        std::sort(vct.begin(), vct.end(), [=](int x, int y)
                  { return dfn[x] < dfn[y]; });

        std::vector<int> used({1}), s({1});
        for (int v : vct)
            if (v ^ 1)
            {
                int lca = getlca(s.back(), v);
                if (lca ^ s.back())
                {
                    while (dfn[lca] < dfn[s.at(s.size() - 2)])
                    {
                        vt[s.at(s.size() - 2)].emplace_back(s.back(), dep[s.back()] - dep[s.at(s.size() - 2)]);
                        s.pop_back();
                    }

                    if (dfn[lca] ^ dfn[s.at(s.size() - 2)])
                    {
                        vt[lca].emplace_back(s.back(), dep[s.back()] - dep[lca]);
                        s.back() = lca;
                        used.push_back(lca);
                    }
                    else
                    {
                        vt[s.at(s.size() - 2)].emplace_back(s.back(), dep[s.back()] - dep[s.at(s.size() - 2)]);
                        s.pop_back();
                    }
                }
                s.push_back(v);
                used.push_back(v);
            }
        for (int i = 1; i < s.size(); ++i)
            vt[s.at(i - 1)].emplace_back(s.at(i), dep[s.at(i)] - dep[s.at(i - 1)]);

        res1 = res3 = 0;
        res2 = INT_MAX / 2;
        for (int v : used)
        {
            cnt[v] = 0;
            min[v] = INT_MAX / 2;
            max[v] = INT_MIN / 2;
        }
        dp(1);

        std::cout << res1 << ' ' << res2 << ' ' << res3 << std::endl;

        for (int v : vct)
            b[v] = false;
        for (int v : used)
            vt[v].clear();
    }
    return 0;
}