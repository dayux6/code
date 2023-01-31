#include <bits/stdc++.h>

void read(int &x)
{
    x = 0;
    char c = std::getchar();
    while (!std::isdigit(c))
        c = std::getchar();
    while (std::isdigit(c))
    {
        x = x * 10 + (c ^ 48);
        c = std::getchar();
    }
}

const int maxn = 1e5, maxrc = 1e6, dx[] = {0, 0, -1, -1, -1, 1, 1, 1}, dy[] = {-1, 1, -1, 0, 1, -1, 0, 1};

int dfc, scnt;
std::array<int, maxrc + 1> rid, cid;
std::array<int, maxn * 3 + 1> dfn, low, scc, sum, ind, f;
std::array<bool, maxn * 3 + 1> ins;
std::stack<int> s;
std::array<std::vector<int>, maxn * 3 + 1> g, dag;
struct hash
{
    long long operator()(std::pair<int, int> pr) const { return 1ll * pr.first * maxrc + pr.second; }
};
std::unordered_map<std::pair<int, int>, int, hash> door;

void tarjan(int x)
{
    ++dfc;
    dfn[x] = low[x] = dfc;

    ins[x] = true;
    s.emplace(x);

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
        int t;
        ++scnt;
        do
        {
            t = s.top();
            s.pop();
            ins[t] = false;
            scc[t] = scnt;
        } while (t != x);
    }
}

int main()
{
    std::freopen("box.in", "r", stdin);
    std::freopen("box.out", "w", stdout);

    int n, r, c;
    read(n), read(r), read(c);

    int tot = n;
    std::vector<std::tuple<int, int, int>> tmp;
    for (int i = 1, x, y, t; i <= n; ++i)
    {
        read(x), read(y), read(t);

        if (rid[x] == 0)
        {
            ++tot;
            rid[x] = tot;
        }
        g[rid[x]].emplace_back(i);
        if (t == 1)
            g[i].emplace_back(rid[x]);

        if (cid[y] == 0)
        {
            ++tot;
            cid[y] = tot;
        }
        g[cid[y]].emplace_back(i);
        if (t == 2)
            g[i].emplace_back(cid[y]);

        door.emplace(std::make_pair(x, y), i);
        if (t == 3)
            tmp.emplace_back(x, y, i);
    }

    for (std::tuple<int, int, int> tp : tmp)
        for (int i = 0; i < 8; ++i)
        {
            int nx = std::get<0>(tp) + dx[i], ny = std::get<1>(tp) + dy[i];
            if (door.count(std::make_pair(nx, ny)))
                g[std::get<2>(tp)].emplace_back(door[std::make_pair(nx, ny)]);
        }

    for (int i = 1; i <= tot; ++i)
        if (dfn[i] == 0)
            tarjan(i);

    for (int i = 1; i <= n; ++i)
        ++sum[scc[i]];

    for (int i = 1; i <= tot; ++i)
    {
        for (int v : g[i])
            if (scc[i] != scc[v])
            {
                ++ind[scc[v]];
                dag[scc[i]].emplace_back(scc[v]);
            }
    }

    std::queue<int> q;
    for (int i = 1; i <= scnt; ++i)
        if (ind[i] == 0)
        {
            f[i] = sum[i];
            q.emplace(i);
        }

    while (!q.empty())
    {
        int x = q.front();
        q.pop();

        for (int v : dag[x])
        {
            --ind[v];
            if (ind[v] == 0)
                q.emplace(v);
            f[v] = std::max(f[v], f[x] + sum[v]);
        }
    }

    int max = 0;
    for (int i = 1; i <= scnt; ++i)
        max = std::max(max, f[i]);

    std::cout << max << std::endl;
    return 0;
}