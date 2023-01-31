#include <bits/stdc++.h>

template <typename T>
void read(T &x)
{
    x = 0;
    char c = std::getchar();

    while (!std::isdigit(c))
        c = std::getchar();
    while (std::isdigit(c))
    {
        x = x * 10 + (c ^ 48);
        c = std::getchar();
    }
}

const int maxn = 1e6;

int t[maxn + 1], p[maxn + 1];

int main()
{
    std::freopen("training.in", "r", stdin);
    std::freopen("training.out", "w", stdout);

    int n, m;
    long long k;
    read(n), read(m), read(k);

    for (int i = 1; i <= n; ++i)
        read(t[i]);
    for (int i = 1; i <= n; ++i)
        read(p[i]);

    int r = 1;
    long long max = LLONG_MIN, pos = 0, sumt = 0, sump = 0;
    std::multiset<int> s1, s2;
    for (int l = 1; l <= n; ++l)
    {
        r = std::max(l, r);
        while (r <= n && sumt <= k)
        {
            if (sump > max)
            {
                max = sump;
                pos = l;
            }

            sumt += t[r];
            sump += p[r];
            int delta = t[r] / 2;

            if (s1.size() < m)
            {
                s1.emplace(delta);
                sumt -= delta;
            }
            else if (!s1.empty() && delta > *s1.begin())
            {
                s2.emplace(*s1.begin());
                sumt += *s1.begin();
                s1.erase(s1.begin());
                s1.emplace(delta);
                sumt -= delta;
            }
            else
                s2.emplace(delta);

            ++r;
        }

        if (sumt <= k && sump > max)
        {
            max = sump;
            pos = l;
        }

        sumt -= t[l];
        sump -= p[l];
        int delta = t[l] / 2;

        if (s1.count(delta) != 0)
        {
            s1.erase(s1.lower_bound(delta));
            sumt += delta;

            if (!s2.empty())
            {
                s1.emplace(*s2.rbegin());
                sumt -= *s2.rbegin();
                s2.erase(std::prev(s2.end()));
            }
        }
        else if (s2.count(delta) != 0)
            s2.erase(delta);
    }

    std::cout << pos << ' ' << max << std::endl;
    return 0;
}