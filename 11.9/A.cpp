#include <bits/stdc++.h>

void read(int &x)
{
    x = 0;
    bool b = true;
    char c = std::getchar();
    while (!std::isdigit(c))
    {
        if (c == '-')
            b = false;
        c = std::getchar();
    }
    while (std::isdigit(c))
    {
        if (b)
            x = x * 10 + (c ^ 48);
        else
            x = x * 10 - (c ^ 48);
        c = std::getchar();
    }
}

const int maxn = 1e5;

int cnt;
std::array<int, maxn + 1> w, l, r, nw;

namespace BIT
{
    int n;
    std::array<int, maxn + 1> t;

    int lowbit(int x) { return x & -x; }

    void modify(int x, int v)
    {
        for (int i = x; i <= n; i += lowbit(i))
            t[i] = std::max(t[i], v);
    }

    int query(int x)
    {
        int ret = 0;
        for (int i = x; i > 0; i -= lowbit(i))
            ret = std::max(ret, t[i]);
        return ret;
    }
};

void dfs(int x)
{
    if (x == 0)
        return;

    ++cnt;
    nw[cnt] = w[x];
    dfs(r[x]);
    dfs(l[x]);
}

int main()
{
    std::freopen("tree.in", "r", stdin);
    std::freopen("tree.out", "w", stdout);

    int n;
    read(n);

    std::vector<int> vct;
    for (int i = 1; i <= n; ++i)
    {
        read(w[i]);
        vct.emplace_back(w[i]);
    }

    std::sort(vct.begin(), vct.end());
    vct.erase(std::unique(vct.begin(), vct.end()), vct.end());
    for (int i = 1; i <= n; ++i)
        w[i] = std::lower_bound(vct.begin(), vct.end(), w[i]) - vct.begin() + 1;

    for (int i = 1; i <= n; ++i)
        read(l[i]), read(r[i]);

    dfs(1);

    BIT::n = vct.size();
    for (int i = 1; i <= n; ++i)
        BIT::modify(nw[i], BIT::query(nw[i] - 1) + 1);

    std::cout << BIT::query(BIT::n) << std::endl;
    return 0;
}