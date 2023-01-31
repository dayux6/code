#include <bits/stdc++.h>

const int maxn = 1e6;

std::array<int, maxn + 1> a;

int main()
{
    freopen("range.in", "r", stdin);
    freopen("range.ans", "w", stdout);

    int n, m;
    std::cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];

    for (int i = 0; i < m; ++i)
    {
        int l, r;
        std::cin >> l >> r;

        bool flg = true;
        std::unordered_set<int> s;
        for (int j = l; j <= r; ++j)
            if (s.count(a[j]))
            {
                puts("0");
                flg = false;
                break;
            }
            else
                s.emplace(a[j]);
        if (flg)
            puts("1");
    }
    return 0;
}