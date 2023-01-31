#include <bits/stdc++.h>

int main()
{
    freopen("B.in", "r", stdin);
    int k, n;
    std::cin >> k >> n;
    int *a = new int[n];
    for (int i = 0; i < n; ++i)
        std::cin >> a[i];
    int l = 0, r = -1, ans = 1;
    std::deque<int> qmin, qmax;
    while (l + ans <= n)
    {
        while (qmin.front() < l)
            qmin.pop_front();
        while (qmax.front() < l)
            qmax.pop_front();
        while (r < n - 1)
        {
            ++r;
            while (!qmin.empty() && a[qmin.back()] >= a[r])
                qmin.pop_back();
            qmin.emplace_back(r);
            while (!qmax.empty() && a[qmax.back()] <= a[r])
                qmax.pop_back();
            qmax.emplace_back(r);
            if (a[qmax.front()] - a[qmin.front()] > k)
                break;
            else
                ans = r - l + 1;
        }
        ++l;
    }
    std::cout << ans << std::endl;
    return 0;
}