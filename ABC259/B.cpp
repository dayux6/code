#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("B.in");
#endif
using std::cout;

typedef long double db;

int main()
{
    int a, b, d;
    cin >> a >> b >> d;
    if (!a && !b)
    {
        std::cout << "0 0" << std::endl;
        return 0;
    }
    db dis = hypot(a, b), r = atan2(b, a) + M_PI * d / 180;
    cout << std::fixed << std::setprecision(12) << dis * cos(r) << ' ' << dis * sin(r) << std::endl;
    return 0;
}