#include <bits/stdc++.h>
#include "ds.h"

int pos[1001], cnt[1001];
std::pair<int, int> prc[1001], prp[1001];

void solve(int n, int lim1, int lim2)
{
    std::vector<int> par, val;
    par.resize(n - 1);
    val.resize(n - 1);

    int tmp;
    for (int i = 1; i < n; ++i)
    {
        if (i != n - 1)
            exchange(i, n - 1);

        for (int j = 2; j <= n; ++j)
        {
            tmp = query(j);
            pos[i] += tmp == n - 1;
            cnt[j] += tmp == n - 1;
        }

        if (i != n - 1)
            exchange(i, n - 1);
    }

    for (int i = 2; i <= n; ++i)
    {
        prc[i].first = cnt[i];
        prc[i].second = i;
    }

    for (int i = 1; i < n; ++i)
    {
        prp[i].first = pos[i];
        prp[i].second = i;
    }

    std::sort(prc + 2, prc + n + 1);
    std::sort(prp + 1, prp + n, std::greater<std::pair<int, int>>());

    prc[1].second = 1;
    for (int i = 2; i <= n; ++i)
    {
        par[prc[i].second - 2] = prc[i - 1].second;
        val[prc[i].second - 2] = prp[i - 1].second;
    }

    answer(par, val);
}