#include <bits/stdc++.h>

const int maxn = 1e5;

int a[maxn + 1], b[maxn + 1];

int main()
{
    freopen("car.in", "r", stdin);
    freopen("car.ans", "w", stdout);

    int n, m;
    std::cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        std::cin >> a[i] >> b[i];

    for (int _ = 0; _ < m; ++_)
    {
        std::string op;
        int l, r, v;
        std::cin >> op >> l >> r >> v;

        if (op == "Set")
            for (int i = l; i <= r; ++i)
                b[i] = v;
        else
            for (int i = l; i <= r; ++i)
                a[i] += v;

        long long res = 0;
        for (int i = 1; i <= n; ++i)
            res += 1ll * a[i] * b[i];
        std::cout << res << std::endl;
    }
    return 0;
}