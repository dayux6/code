#include <bits/stdc++.h>

const int maxn = 45, maxm = 10000;

int n, per[maxn];
bool b;
std::bitset<maxn + 1> flg;
std::bitset<maxm> bel[maxn + 1];

void dfs(int d)
{
    if (d == n)
    {
        if ((bel[per[n - 2]] & bel[per[n - 1]] & bel[per[0]]).count() == 0 && (bel[per[n - 1]] & bel[per[0]] & bel[per[1]]).count() == 0)
        {
            for (int i = 0; i < n; ++i)
                std::cout << per[i] << ' ';
            std::cout << '\n';
            b = true;
        }
        return;
    }

    for (int i = 1; i <= n; ++i)
        if (!flg[i] && (d < 1 || (bel[per[d - 2]] & bel[per[d - 1]] & bel[i]).count() == 0))
        {
            flg.set(i);
            per[d] = i;
            dfs(d + 1);
            flg.reset(i);
            if (b)
                return;
        }
}

void solve()
{
    int m;
    std::cin >> n >> m;

    for (int i = 0, k; i < m; ++i)
    {
        std::cin >> k;
        for (int j = 0, x; j < k; ++j)
        {
            std::cin >> x;
            bel[x].set(i);
        }
    }

    b = false;
    flg.reset();
    flg.set(1);
    per[0] = 1;
    dfs(1);

    if (!b)
        std::puts("-1");

    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < m; ++j)
            bel[i].reset(j);
}

int main()
{
    std::freopen("contest.in", "r", stdin);
    std::freopen("contest.out", "w", stdout);

    int t;
    std::cin >> t;

    for (int i = 0; i < t; ++i)
        solve();
    return 0;
}