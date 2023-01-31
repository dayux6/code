#include <bits/stdc++.h>

#pragma GCC optimize(2, 3, "Ofast")

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("CF1702F.in");
#endif
using std::cout;

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    for (int _ = 0; _ < t; ++_)
    {
        int n;
        cin >> n;
        std::unordered_map<int, int> cnt;
        for (int i = 0; i < n; ++i)
        {
            int v;
            cin >> v;
            while (v % 2 == 0)
                v /= 2;
            ++cnt[v];
        }
        bool b = true;
        for (int i = 0; i < n; ++i)
        {
            int v;
            cin >> v;
            while (v > 1 && cnt.count(v) == 0)
                v /= 2;
            if (cnt.count(v) == 0)
                b = false;
            else
            {
                --cnt[v];
                if (cnt[v] == 0)
                    cnt.erase(v);
            }
        }
        if (b)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}