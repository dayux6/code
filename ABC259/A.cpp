#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("A.in");
#endif
using std::cout;

int main()
{
    int n, m, x, t, d;
    cin >> n >> m >> x >> t >> d;
    if (m >= x)
        cout << t << std::endl;
    else
        cout << t - (x - m) * d << std::endl;
    return 0;
}