#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("CF1703C.in");
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
        int *a = new int[n];
        for (int i = 0; i < n; ++i)
            cin >> a[i];
        for (int i = 0; i < n; ++i)
        {
            int m;
            std::string s;
            cin >> m >> s;
            for (int j = 0; j < m; ++j)
                switch (s.at(j))
                {
                case 'U':
                    a[i]--;
                    break;
                case 'D':
                    a[i]++;
                    break;
                }
        }
        for (int i = 0; i < n; ++i)
            cout << (a[i] % 10 + 10) % 10 << ' ';
        cout << '\n';
    }
    return 0;
}