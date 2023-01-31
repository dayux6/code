#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("E.in");
#endif
using std::cout;

int main()
{
    int n;
    cin >> n;
    int *m = new int[n];
    std::pair<int, int> **pr = new std::pair<int, int> *[n];
    std::unordered_map<int, std::pair<int, int>> max;
    for (int i = 0; i < n; ++i)
    {
        cin >> m[i];
        pr[i] = new std::pair<int, int>[m[i]];
        for (int j = 0; j < m[i]; ++j)
        {
            cin >> pr[i][j].first >> pr[i][j].second;
            if (max[pr[i][j].first].first < pr[i][j].second)
                max[pr[i][j].first] = std::make_pair(pr[i][j].second, 1);
            else if (max[pr[i][j].first].first == pr[i][j].second)
                ++max[pr[i][j].first].second;
        }
    }
    int cnt = 0;
    bool flg = true;
    for (int i = 0; i < n; ++i)
    {
        bool b = false;
        for (int j = 0; j < m[i]; ++j)
            if (pr[i][j].second == max[pr[i][j].first].first && max[pr[i][j].first].second < 2)
            {
                b = true;
                break;
            }
        cnt += b;
        if (flg && !b)
        {
            ++cnt;
            flg = false;
        }
    }
    std::cout << cnt << std::endl;
    return 0;
}