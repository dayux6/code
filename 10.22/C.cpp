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

void write(int x)
{
    static int t = 0, s[10];

    do
    {
        s[t] = x % 10;
        x /= 10;
        ++t;
    } while (x != 0);

    while (t > 0)
    {
        --t;
        putchar(s[t] + 48);
    }
    putchar('\n');
}

const int maxn = 2e5, maxr = 2.5e4;

int h[maxn + 1], cnt[maxr + 1], pre[maxr + 1], dfc, dfn[maxn + 1], end[maxn + 1];
std::vector<int> s[maxn + 1], col[maxr + 1];
std::vector<std::pair<int, int>> rg[maxr + 1];
std::unordered_map<int, int> ans[maxr + 1];

void dfs(int x, int fa)
{
    ++cnt[h[x]];
    ++pre[h[x]];
    ++dfc;
    dfn[x] = dfc;
    col[h[x]].emplace_back(dfc);
    rg[h[x]].emplace_back(dfc, pre[h[x]]);

    for (int v : s[x])
        if (v != fa)
            dfs(v, x);

    --pre[h[x]];
    end[dfn[x]] = dfc;
    rg[h[x]].emplace_back(dfc, pre[h[x]]);
}

int calc1(int h1, int h2)
{
    int ret = 0;
    for (int v : col[h1])
        ret += std::upper_bound(col[h2].begin(), col[h2].end(), end[v]) - std::upper_bound(col[h2].begin(), col[h2].end(), v);
    return ret;
}

int calc2(int h1, int h2)
{
    int ret = 0;
    for (int v : col[h2])
    {
        auto it = std::upper_bound(rg[h1].begin(), rg[h1].end(), std::make_pair(v, -1));
        if (it != rg[h1].begin())
            ret += std::prev(it)->second;
    }
    return ret;
}

int calc3(int h1, int h2)
{
    int ret = 0;
    auto it = rg[h1].begin();
    for (int v : col[h2])
    {
        while (it != rg[h1].end() && it->first < v)
            it = std::next(it);
        if (it != rg[h1].begin())
            ret += std::prev(it)->second;
    }
    return ret;
}

int main()
{
    std::freopen("regions.in", "r", stdin);
    std::freopen("regions.out", "w", stdout);

    int n, r, q;
    read(n);
    read(r);
    read(q);
    read(h[1]);

    for (int i = 2; i <= n; ++i)
    {
        int fa;
        read(fa);
        s[fa].emplace_back(i);
        read(h[i]);
    }

    dfs(1, 1);

    for (int i = 0; i < q; ++i)
    {
        int h1, h2;
        read(h1);
        read(h2);

        if (ans[h1].count(h2) == 0)
        {
            int min = std::min({cnt[h1] * (int)std::log2(cnt[h2]), (int)std::log2(cnt[h1]) * cnt[h2], cnt[h1] + cnt[h2]});

            if (min == cnt[h1] * (int)std::log2(cnt[h2]))
                ans[h1].emplace(h2, calc1(h1, h2));
            else if (min == (int)std::log2(cnt[h1]) * cnt[h2])
                ans[h1].emplace(h2, calc2(h1, h2));
            else
                ans[h1].emplace(h2, calc3(h1, h2));
        }

        write(ans[h1][h2]);
    }
    return 0;
}