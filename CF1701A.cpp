#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("CF1701A.in");
#endif
using std::cout;

int main()
{
    int t;
    cin >> t;
    for (int _ = 0; _ < t; ++_)
    {
        int cnt = 0;
        for (int i = 0; i < 4; ++i)
        {
            int a;
            cin >> a;
            cnt += a != 0;
        }
        if (cnt == 0)
            cout << 0 << '\n';
        else if (cnt == 4)
            cout << 2 << '\n';
        else
            cout << 1 << '\n';
    }
    return 0;
}