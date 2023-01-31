#include <bits/stdc++.h>

struct cow
{
    int x, h;

    cow() { std::cin >> x >> h; }

    bool operator<(cow rhs) const { return x < rhs.x; }
};

int main()
{
    freopen("D.in", "r", stdin);
    int n, d;
    std::cin >> n >> d;
    cow *c = new cow[n]();
    std::sort(c, c + n);
    std::vector<int> vct;
    for (int i = 0; i < n; ++i)
        vct.emplace_back(c[i].x);
    vct.erase(std::unique(vct.begin(), vct.end()), vct.end());
    int *l = new int[n], *r = new int[n];
    for (int i = 0; i < n; ++i)
    {
        l[i] = std::lower_bound(vct.begin(), vct.end(), c[i].x - d) - vct.begin();
        r[i] = --std::upper_bound(vct.begin(), vct.end(), c[i].x + d) - vct.begin();
    }
    int lg = log2(n), **st = new int *[n];
    for (int i = 0; i < n; ++i)
    {
        st[i] = new int[lg + 1]();
        st[i][0] = c[i].h;
    }
    for (int i = 1; i <= lg; ++i)
        for (int j = 0; j + (1 << i) - 1 < n; ++j)
            st[j][i] = std::max(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
    auto query = [=](int l, int r)
    {
        if (l > r)
            return -1;
        int k = log2(r - l + 1);
        return std::max(st[l][k], st[r - (1 << k) + 1][k]);
    };
    int cnt = 0;
    for (int i = 0; i < n; ++i)
        cnt += (query(l[i], i - 1) >= c[i].h * 2) && (query(i + 1, r[i]) >= c[i].h * 2);
    std::cout << cnt << std::endl;
    return 0;
}