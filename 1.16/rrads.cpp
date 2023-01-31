#include <bits/stdc++.h>

const int maxn = 5e5;

void read(int &x)
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

int a[maxn + 1], bel[maxn + 1];
long long ans[maxn];

struct query
{
    int l, r, id;

    bool operator<(query rhs) const { return bel[l] ^ bel[rhs.l] ? bel[l] < bel[rhs.l] : (bel[l] & 1) ^ (r < rhs.r); }
} q[maxn];

int main()
{
    std::freopen("rrads.in", "r", stdin);
    std::freopen("rrads.out", "w", stdout);

    int n, m;
    read(n), read(m);

    int bsiz = std::sqrt(n * std::log2(n));
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        bel[i] = (i - 1) / bsiz + 1;
    }

    for (int i = 0; i < m; ++i)
    {
        read(q[i].l), read(q[i].r);
        q[i].id = i;
    }
    std::sort(q, q + m);

    long long res = 0;
    std::set<std::pair<int, int>> s;
    auto ins = [&](int p)
    {
        auto pr = std::make_pair(a[p], p);
        s.emplace(pr);
        auto it = s.lower_bound(pr);
        if (it != s.begin())
            res += std::abs(p - std::prev(it)->second);
        if (!s.empty() && std::next(it) != s.end())
            res += std::abs(p - std::next(it)->second);
        if (!s.empty() && it != s.begin() && std::next(it) != s.end())
            res -= std::abs(std::prev(it)->second - std::next(it)->second);
    };
    auto del = [&](int p)
    {
        auto pr = std::make_pair(a[p], p);
        auto it = s.lower_bound(pr);
        if (it != s.begin())
            res -= std::abs(p - std::prev(it)->second);
        if (!s.empty() && std::next(it) != s.end())
            res -= std::abs(p - std::next(it)->second);
        if (!s.empty() && it != s.begin() && std::next(it) != s.end())
            res += std::abs(std::prev(it)->second - std::next(it)->second);
        s.erase(pr);
    };

    int l = 1, r = 0;
    for (int i = 0; i < m; ++i)
    {
        while (r < q[i].r)
        {
            ++r;
            ins(r);
        }
        while (l > q[i].l)
        {
            --l;
            ins(l);
        }
        while (r > q[i].r)
        {
            del(r);
            --r;
        }
        while (l < q[i].l)
        {
            del(l);
            ++l;
        }

        ans[q[i].id] = res;
    }

    for (int i = 0; i < m; ++i)
        std::cout << ans[i] << '\n';
    return 0;
}