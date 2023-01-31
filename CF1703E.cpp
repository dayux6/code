#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("CF1703E.in");
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
        bool **a = new bool *[n];
        for (int i = 0; i < n; ++i)
        {
            std::string s;
            cin >> s;
            a[i] = new bool[n];
            for (int j = 0; j < n; ++j)
                a[i][j] = s.at(j) == '1';
        }
        bool **vis = new bool *[n];
        for (int i = 0; i < n; ++i)
            vis[i] = new bool[n]();
        int sum = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (!vis[i][j])
                {
                    int nx = n - i - 1, ny = n - j - 1, cnt[2];
                    cnt[0] = cnt[1] = 0;
                    cnt[a[i][j]]++;
                    cnt[a[ny][i]]++;
                    cnt[a[nx][ny]]++;
                    cnt[a[j][nx]]++;
                    sum += std::min(cnt[0], cnt[1]);
                    vis[i][j] = vis[ny][i] = vis[nx][ny] = vis[j][nx] = true;
                }
        cout << sum << '\n';
    }
    return 0;
}