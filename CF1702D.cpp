#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("CF1702D.in");
#endif
using std::cout;

int main()
{
    int t;
    cin >> t;
    for (int _ = 0; _ < t; ++_)
    {
        std::string s;
        int p;
        cin >> s >> p;
        int sum = 0;
        std::vector<int> pos[26];
        for (int i = 0; i < 26; ++i)
            pos[i].clear();
        for (int i = 0; i < s.size(); ++i)
        {
            sum += s.at(i) - 'a' + 1;
            pos[s.at(i) - 'a'].emplace_back(i);
        }
        if (sum <= p)
            cout << s << '\n';
        else
        {
            bool *b = new bool[s.size()]();
            for (int i = 25; i >= 0; --i)
            {
                for (int j : pos[i])
                {
                    b[j] = true;
                    sum -= i + 1;
                    if (sum <= p)
                        break;
                }
                if (sum <= p)
                    break;
            }
            for (int i = 0; i < s.size(); ++i)
                if (!b[i])
                    cout << s.at(i);
            cout << '\n';
        }
    }
    return 0;
}