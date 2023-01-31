#include <bits/stdc++.h>

const int maxn = 2e5;

std::array<int, maxn> p;

long long solve()
{
    int n;
    std::cin >> n;

    for (int i = 1; i <= n; ++i)
    {
        int a;
        std::cin >> a;
        p[a] = i;
    }

    int l = n, r = 1;
    long long ret = 0;
    for (int mex = 1; mex < n; ++mex)
    {
        l = std::min(l, p[mex - 1]);
        r = std::max(r, p[mex - 1]);

        if (p[mex] < l)
            for (int i = p[mex] + 1; i <= l; ++i)
                ret += std::max(0, std::min(i + mex * 2 - 1, n) - r + 1);
        else if (p[mex] > r)
            for (int i = r; i < p[mex]; ++i)
                ret += std::max(0, l - std::max(i - mex * 2 + 1, 1) + 1);
    }

    return ret + 1;
}

int main()
{
    std::freopen("CF1744F.in", "r", stdin);

    int t;
    std::cin >> t;

    for (int i = 0; i < t; ++i)
        std::cout << solve() << std::endl;
    return 0;
}