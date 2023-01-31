#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("CF1703D.in");
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
        std::string *s = new std::string[n];
        std::unordered_set<std::string> vis;
        for (int i = 0; i < n; ++i)
        {
            cin >> s[i];
            vis.emplace(s[i]);
        }
        for (int i = 0; i < n; ++i)
        {
            bool b = true;
            for (int j = 1; j < s[i].size(); ++j)
                if (vis.count(s[i].substr(0, j)) != 0 && vis.count(s[i].substr(j)) != 0)
                {
                    b = false;
                    cout << '1';
                    break;
                }
            if (b)
                cout << '0';
        }
        cout << '\n';
    }
    return 0;
}