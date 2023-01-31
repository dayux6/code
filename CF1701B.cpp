#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("CF1701B.in");
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
        cout << "2\n";
        int *vis = new int[n + 1]();
        for (int i = 1; i <= n; ++i)
            if (!vis[i])
                for (int j = i; j <= n; j *= 2)
                {
                    vis[j] = true;
                    cout << j << ' ';
                }
        cout << '\n';
    }
    return 0;
}