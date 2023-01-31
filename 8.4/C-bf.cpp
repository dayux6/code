#include <bits/stdc++.h>

const int maxn = 20;

int n, p[maxn + 1], c[maxn + 1];
bool flg[maxn + 1];

int dfs(int d)
{
    if (d == n + 1)
    {
        bool b = true;
        for (int i = 1; i <= n; ++i)
            if (!flg[i])
            {
                b = false;
                break;
            }
        return b ? 0 : INT_MAX / 2;
    }

    int ret = dfs(d + 1);

    if (!flg[d])
    {
        flg[d] = true;
        std::vector<int> vct({d});
        for (int i = 1; i < d; ++i)
            if (!flg[i] && p[i] > p[d])
            {
                flg[i] = true;
                vct.push_back(i);
            }
        for (int i = d + 1; i <= n; ++i)
            if (!flg[i] && p[i] < p[d])
            {
                flg[i] = true;
                vct.push_back(i);
            }

        ret = std::min(ret, c[d] + dfs(d + 1));

        for (int i : vct)
            flg[i] = false;
    }
    return ret;
}

int main()
{
    freopen("C.in", "r", stdin);
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
        std::cin >> p[i];
    for (int i = 1; i <= n; ++i)
        std::cin >> c[i];
    std::cout << dfs(1) << std::endl;
    return 0;
}