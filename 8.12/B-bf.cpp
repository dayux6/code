#include <bits/stdc++.h>

int qpow(int x, int n)
{
    int ret = 1;
    while (n)
    {
        if (n & 1)
            ret = ret * x;
        x = x * x;
        n /= 2;
    }
    return ret;
}

long long calc(int x)
{
    if (x == 1)
        return 1;

    std::vector<std::pair<int, int>> vct;
    for (int i = 2; i * i <= x; ++i)
        if (x % i == 0)
        {
            int cnt = 0;
            while (x % i == 0)
            {
                ++cnt;
                x /= i;
            }
            vct.emplace_back(i, cnt);
        }
    if (x != 1)
        vct.emplace_back(x, 1);

    if (vct.size() == 1)
        return vct.back().first ^ vct.back().second;
    else
    {
        long long ret = 1;
        for (std::pair<int, int> pr : vct)
            ret *= (pr.first ^ pr.second);
        return ret;
    }
}

int main()
{
    freopen("B.out", "w", stdout);
    int n = 5e7;
    long long sum = 0;
    for (int i = 1; i <= n; ++i)
    {
        sum += calc(i);

        if (i % 50000 == 0)
            std::cout << sum << ',';
    }
    return 0;
}