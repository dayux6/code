#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("CF1701D.in");
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
        std::vector<std::pair<int, int>> *l = new std::vector<std::pair<int, int>>[n + 1];
        for (int i = 0; i < n; ++i)
        {
            int b;
            cin >> b;
            l[std::min(n, (i + 1) / (b + 1) + 1)].emplace_back(i, b ? (i + 1) / b : n);
        }
        int *ans = new int[n + 1];
        std::priority_queue<std::pair<int, int>> q;
        for (int i = 1; i <= n; ++i)
        {
            for (std::pair<int, int> pr : l[i])
                q.emplace(-pr.second, pr.first);
            ans[q.top().second] = i;
            q.pop();
        }
        for (int i = 0; i < n; ++i)
            cout << ans[i] << ' ';
        cout << '\n';
    }
    return 0;
}