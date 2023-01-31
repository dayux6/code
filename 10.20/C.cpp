#include <bits/stdc++.h>

const int maxn = 100, maxs = 100;

int a[maxn], c[maxs + 1];

int main()
{
    std::freopen("C.in", "r", stdin);

    int n;
    std::cin >> n;

    int lim = 0;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> a[i];
        ++c[a[i]];
        lim = std::max(lim, a[i]);
    }

    std::unordered_set<int> s, t;
    for (int i = 1; i <= lim; ++i)
        if (c[i] == 1)
            s.insert(i);
        else if (c[i] > 2)
            t.insert(i);

    if ((s.size() & 1) && t.empty())
        std::cout << "NO" << std::endl;
    else
    {
        std::cout << "YES" << std::endl;

        int tags;
        bool tag, b = false, flg = false;
        for (int i = 0; i < n; ++i)
            if (s.count(a[i]) != 0)
            {
                std::cout << (b ? 'B' : 'A');
                b ^= 1;
            }
            else if ((s.size() & 1) && !flg && t.count(a[i]) != 0)
            {
                std::cout << (b ? 'B' : 'A');
                b ^= 1;
                tags = a[i];
                tag = b;
                flg = true;
            }
            else if (a[i] == tags)
                std::cout << (tag ? 'B' : 'A');
            else
                std::cout << 'A';
        std::cout << std::endl;
    }
    return 0;
}