#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("CF1702A.in");
#endif
using std::cout;

int main()
{
    int t;
    cin >> t;
    for (int _ = 0; _ < t; ++_)
    {
        int m;
        cin >> m;
        int n = 1;
        while (n * 10 <= m)
            n *= 10;
        cout << m - n << std::endl;
    }
    return 0;
}