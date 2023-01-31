#include <bits/stdc++.h>

const double eps = 1e-6;

int main()
{
    freopen("E.in", "r", stdin);
    int n;
    std::cin >> n;
    int *a = new int[n + 1], sum = 0;
    double r = 0;
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> a[i];
        sum += a[i];
        r = std::max(r, (double)a[i]);
    }
    auto check = [=](double k)
    {
        double s = 0;
        for (int i = 2; i < n; ++i)
        {
            s += a[i] - k;
            if (s >= sum - n * k)
                return true;
            if (s < 0)
                s = 0;
        }
        return false;
    };
    double l = 0, ans = r;
    while (r - l >= eps)
    {
        double mid = (l + r) / 2;
        if (check(mid))
        {
            ans = mid;
            r = mid;
        }
        else
            l = mid;
    }
    std::cout << std::fixed << std::setprecision(3) << round(ans * 1000) / 1000 << std::endl;
    return 0;
}