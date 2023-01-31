#include <bits/stdc++.h>

int main()
{
    freopen("A.in", "r", stdin);
    int n, m, q;
    std::cin >> n >> m >> q;

    if (n < m)
        std::swap(n, m);

    auto calc = [=](int k)
    {
        int r;
        long long ret = 0;
        for (int l = 1; l <= k; l = r + 1)
        {
            r = k / (k / l);
            ret += 1ll * (r - l + 1) * (k / l);
        }
        return ret;
    };

    for (int i = 0; i < q; ++i)
    {
        int k;
        std::cin >> k;

        int l = 1, r = k, ans;
        while (l <= r)
        {
            int mid = (l + r) / 2;

            if (calc(mid) < k)
                l = mid + 1;
            else
            {
                r = mid - 1;
                ans = mid;
            }
        }
        std::cout << ans << std::endl;
    }
    return 0;
}