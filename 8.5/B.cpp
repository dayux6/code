#include <bits/stdc++.h>

const int maxm = 1e3;

int c[maxm], x[maxm], y[maxm], z[maxm];

int main()
{
    freopen("B.in", "r", stdin);
    int m, k;
    std::cin >> m >> k;
    for (int i = 0; i < m; ++i)
        std::cin >> c[i];
    for (int i = 0; i < m; ++i)
        std::cin >> x[i];
    for (int i = 0; i < m; ++i)
        std::cin >> y[i];
    for (int i = 0; i < m; ++i)
        std::cin >> z[i];
    int s = (1 << k) - 1, cnt = 0, val;
    std::vector<int> vct;
    auto ins = [&](int v)
    {
        if (cnt == 0)
            val = v;
        if (val == v)
            ++cnt;
        else
            --cnt;
    };
    for (int i = 0; i < m; ++i)
    {
        long long tmp = x[i];
        ins(tmp);
        for (int j = 1; j < c[i]; ++j)
        {
            tmp = (tmp * y[i] + z[i]) & s;
            ins(tmp);
        }
    }
    if (cnt == 0)
        std::cout << 0 << std::endl;
    else
    {
        cnt = 0;
        int n = 0;
        for (int i = 0; i < m; ++i)
        {
            long long tmp = x[i];
            cnt += tmp == val;
            for (int j = 1; j < c[i]; ++j)
            {
                tmp = (tmp * y[i] + z[i]) & s;
                cnt += tmp == val;
            }
            n += c[i];
        }
        if (cnt * 2ll > n)
            std::cout << cnt - (n - cnt + 1) << std::endl;
        else
            std::cout << 0 << std::endl;
    }
    return 0;
}