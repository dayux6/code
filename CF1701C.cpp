#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("CF1701C.in");
#endif
using std::cout;

int main()
{
    int t;
    cin >> t;
    for (int _ = 0; _ < t; ++_)
    {
        int n, m;
        cin >> n >> m;
        int *c = new int[n + 1]();
        for (int i = 0; i < m; ++i)
        {
            int a;
            cin >> a;
            c[a]++;
        }
        auto check = [=](int k)
        {
            long long cnt = 0;
            for (int i = 1; i <= n; ++i)
                if (c[i] < k)
                    cnt += (k - c[i]) / 2;
                else
                    cnt -= c[i] - k;
            return cnt >= 0;
        };
        int l = 1, r = m * 2, ans;
        while (l <= r)
        {
            int mid = (l + r) / 2;
            if (check(mid))
            {
                ans = mid;
                r = mid - 1;
            }
            else
                l = mid + 1;
        }
        cout << ans << '\n';
    }
    return 0;
}