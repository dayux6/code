#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("CF1703B.in");
#endif
using std::cout;

int main()
{
    int t;
    cin >> t;
    for (int _ = 0; _ < t; ++_)
    {
        int n;
        std::string s;
        cin >> n >> s;
        int cnt = 0;
        std::unordered_set<char> vis;
        for (int i = 0; i < n; ++i)
            if (vis.count(s.at(i)) == 0)
            {
                cnt++;
                vis.insert(s.at(i));
            }
        std::cout << n + cnt << '\n';
    }
    return 0;
}