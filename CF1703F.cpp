#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("CF1703F.in");
#endif
using std::cout;

int main()
{
    int t;
    cin >> t;
    for (int _ = 0; _ < t; ++_)
    {
        int n;
        cin >> n;
        int *s = new int[n + 1];
        long long cnt = 0;
        s[0] = 0;
        for (int i = 1; i <= n; ++i)
        {
            int a;
            cin >> a;
            s[i] = s[i - 1];
            if (a < i)
            {
                if (a > 0)
                    cnt += s[a - 1];
                s[i]++;
            }
        }
        cout << cnt << '\n';
    }
    return 0;
}