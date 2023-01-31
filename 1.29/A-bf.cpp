#include <bits/stdc++.h>

const int maxn = 1e5;

int a[maxn], l[maxn], r[maxn];

int main()
{
    std::freopen("tournament.in", "r", stdin);
    std::freopen("tournament.ans", "w", stdout);

    int n, c, w;
    std::cin >> n >> c >> w;

    for (int i = 1; i < n; ++i)
        std::cin >> a[i];

    for (int i = 0; i < c; ++i)
        std::cin >> l[i] >> r[i];

    int ans = INT_MIN, pos;
    std::deque<int> q;
    for (int i = 0; i < n; ++i)
    {
        std::deque<int>().swap(q);

        for (int j = 1; j <= i; ++j)
            q.emplace_back(a[j]);
        q.emplace_back(w);
        for (int j = i + 1; j < n; ++j)
            q.emplace_back(a[j]);

        int cnt = 0;
        for (int j = 0; j < c; ++j)
        {
            int max = 0;
            bool flg = false;
            for (int k = l[j]; k <= r[j]; ++k)
            {
                max = std::max(max, q[k]);
                if (q[k] == w)
                    flg = true;
            }
            q.erase(q.begin() + l[j], q.begin() + r[j] + 1);
            q.emplace(q.begin() + l[j], max);

            if (flg)
            {
                if (max > w)
                    break;
                else
                    ++cnt;
            }
        }

        if (cnt > ans)
        {
            ans = cnt;
            pos = i;
        }
    }

    std::cout << pos << std::endl;
    return 0;
}