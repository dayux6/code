#include <bits/stdc++.h>

const int maxn = 2e5;

int n;

class BIT
{
private:
    int t[maxn + 1];

    inline int lowbit(int x) { return x & -x; }

public:
    void clear() { std::fill_n(t + 1, n, 0); }

    void modify(int x)
    {
        for (int i = x; i <= n; i += lowbit(i))
            ++t[i];
    }

    int query(int x)
    {
        int ret = 0;
        for (int i = x; i > 0; i -= lowbit(i))
            ret += t[i];
        return ret;
    }
} t[2];

int main()
{
    std::freopen("xor.in", "r", stdin);
    std::freopen("xor.out", "w", stdout);

    std::cin >> n;

    long long max = 0, a[n];
    for (int i = 0; i < n; ++i)
    {
        std::cin >> a[i];
        max = std::max(max, a[i]);
    }
    std::sort(a, a + n);

    long long ans = 0, suf[n];
    std::fill_n(suf, n, 0);
    BIT t[2];
    for (int i = 0; (1ll << i) <= max; ++i)
    {
        std::vector<long long> vs;
        for (int j = 0; j < n; ++j)
            vs.emplace_back(suf[j]);

        std::sort(vs.begin(), vs.end());
        vs.erase(std::unique(vs.begin(), vs.end()), vs.end());

        bool b = 0;
        for (int j = 0, rk; j < n; ++j)
        {
            rk = std::lower_bound(vs.begin(), vs.end(), suf[j]) - vs.begin() + 1;

            bool k = (a[j] >> i) & 1;
            b ^= (t[k].query(vs.size()) - t[k].query(rk) + t[k ^ 1].query(rk)) & 1;

            t[k].modify(rk);
        }

        if (b)
            ans |= 1ll << i;

        t[0].clear();
        t[1].clear();
        for (int j = 0; j < n; ++j)
            suf[j] |= a[j] & (1ll << i);
    }

    std::cout << ans << std::endl;
    return 0;
}