#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("CF1703A.in");
#endif
using std::cout;

int main()
{
    int t;
    cin >> t;
    for (int _ = 0; _ < t; ++_)
    {
        std::string s;
        cin >> s;
        if ((s.at(0) == 'y' || s.at(0) == 'Y') && (s.at(1) == 'e' || s.at(1) == 'E') && (s.at(2) == 's' || s.at(2) == 'S'))
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}