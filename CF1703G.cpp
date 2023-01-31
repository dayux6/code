#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("CF1703G.in");
#endif
using std::cout;

int main()
{
    int t;
    cin >> t;
    for (int _ = 0; _ < t; ++_)
    {
        int n, k;
        cin >> n >> k;
        int max = 0, *a = new int[n + 1];
        a[0] = 0;
        for (int i = 1; i <= n; ++i)
        {
            cin >> a[i];
            max = std::max(max, a[i]);
        }
        int lg = log2(max) + 1;
        long long pre = k, ans = 0;
        for (int i = 0; i <= n; ++i)
        {
            pre += a[i] - k;
            long long sum = pre;
            for (int j = 1; j <= lg && i + j <= n; ++j)
                sum += a[i + j] >> j;
            ans = std::max(ans, sum);
        }
        cout << ans << '\n';
    }
    return 0;
}