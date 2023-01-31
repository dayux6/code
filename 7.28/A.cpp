#include <bits/stdc++.h>

#pragma GCC optimize(2, 3, "Ofast")

const int maxn = 50, maxk = 50;

int k, tp[maxn + 1], sa, sb, sc, sd, a[maxn + 1], b[maxn + 1], c[maxn + 1], d[maxn + 1];
long long max = 0;

struct equip
{
    int a, b, c, d;

    equip(int _a, int _b, int _c, int _d) : a(_a), b(_b), c(_c), d(_d) {}
};
std::vector<equip> eq[maxk];

void dfs(int dep)
{
    if (dep == k)
    {
        max = std::max(max, 1ll * sa * sb * sc * sd);
        return;
    }
    for (equip i : eq[dep])
    {
        sa += i.a;
        sb += i.b;
        sc += i.c;
        sd += i.d;
        dfs(dep + 1);
        sa -= i.a;
        sb -= i.b;
        sc -= i.c;
        sd -= i.d;
    }
}

int main()
{
    freopen("A.in", "r", stdin);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n;
    std::cin >> n >> k;
    std::vector<int> vct;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> tp[i] >> a[i] >> b[i] >> c[i] >> d[i];
        vct.emplace_back(tp[i]);
    }
    std::sort(vct.begin(), vct.end());
    vct.erase(std::unique(vct.begin(), vct.end()), vct.end());
    k = vct.size();
    for (int i = 0; i < n; ++i)
        eq[std::lower_bound(vct.begin(), vct.end(), tp[i]) - vct.begin()].emplace_back(a[i], b[i], c[i], d[i]);
    sa = sb = sc = sd = 100;
    dfs(0);
    std::cout << max << std::endl;
    return 0;
}