#include <bits/stdc++.h>

const int maxn = 1e5;

int n, p[maxn + 1];
std::vector<int> vct;

struct pair
{
    int a, b, w;
} pr[maxn + 1];

class BIT
{
private:
    int n;
    std::pair<long long, int> t[maxn * 2 + 1];
    int lowbit(int x) { return x & -x; }

public:
    void clear() { std::fill_n(t + 1, n, std::make_pair(0, INT_MIN)); }

    void build(int _n)
    {
        n = _n;
        clear();
    }

    void modify(int x, std::pair<long long, int> v)
    {
        for (int i = x; i <= n; i += lowbit(i))
            t[i] = std::max(t[i], v);
    }

    std::pair<long long, int> query(int x)
    {
        std::pair<long long, int> ret = std::make_pair(0, INT_MIN);
        for (int i = x; i > 0; i -= lowbit(i))
            ret = std::max(ret, t[i]);
        return ret;
    }
} t;

long long dp()
{
    t.clear();

    t.modify(pr[p[1]].a, std::make_pair(pr[p[1]].w, -pr[p[1]].a));
    for (int i = 2; i <= n; ++i)
    {
        std::pair<long long, int> tmp = t.query(pr[p[i]].b);
        t.modify(std::max(-tmp.second, pr[p[i]].a), std::make_pair(tmp.first + pr[p[i]].w, -std::max(-tmp.second, pr[p[i]].a)));
    }
    return t.query(n).first;
}

int main()
{
    freopen("B.in", "r", stdin);
    std::cin >> n;

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> pr[i].a >> pr[i].b >> pr[i].w;
        vct.push_back(pr[i].a);
        vct.push_back(pr[i].b);
    }

    std::sort(vct.begin(), vct.end());
    vct.erase(std::unique(vct.begin(), vct.end()), vct.end());
    for (int i = 1; i <= n; ++i)
    {
        pr[i].a = std::lower_bound(vct.begin(), vct.end(), pr[i].a) - vct.begin() + 1;
        pr[i].b = std::lower_bound(vct.begin(), vct.end(), pr[i].b) - vct.begin() + 1;
    }

    long long ans = 0;
    std::iota(p + 1, p + n + 1, 1);
    t.build(vct.size());
    if (n <= 8)
    {
        do
            ans = std::max(ans, dp());
        while (std::next_permutation(p + 1, p + n + 1));
    }
    else
    {
        srand(time(nullptr));
        while (clock() / CLOCKS_PER_SEC <= 0.99)
        {
            long long res = ans;
            for (double temp = 1e6; temp >= 1e-6; temp *= 0.999)
            {
                int p1 = (long long)std::round(rand() * temp) % n + 1, p2 = (long long)std::round(rand() * temp) % n + 1;
                std::swap(p[p1], p[p2]);
                long long tmp = dp();
                if (tmp <= res && exp((res - tmp) / temp) <= rand())
                    std::swap(p[p1], p[p2]);
                else
                    res = tmp;
            }
            ans = std::max(ans, res);
        }
    }
    std::cout << ans << std::endl;
    return 0;
}