#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("CF1702B.in");
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
        int cnt = 0;
        std::unordered_set<char> vis;
        for (int c : s)
        {
            vis.emplace(c);
            if (vis.size() == 4)
            {
                cnt++;
                vis.clear();
                vis.emplace(c);
            }
        }
        cout << cnt + 1 << std::endl;
    }
    return 0;
}