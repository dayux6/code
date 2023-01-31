#include <bits/stdc++.h>

const int maxn = 3e3;

int a[maxn + 1], b[maxn + 1], c[maxn + 1];

class BIT
{
private:
    int n, t[maxn + 1];

    int lowbit(int x) { return x & -x; }

public:
    void build(int _n) { n = _n; }

    void modify(int x, int v)
    {
        for (int i = x; i <= n; i += lowbit(i))
            t[i] = std::max(t[i], v);
    }

    int query(int x)
    {
        int ret = 0;
        for (int i = x; i > 0; i -= lowbit(i))
            ret = std::max(ret, t[i]);
        return ret;
    }
} t[maxn + 1];

int main()
{
    freopen("A.in", "r", stdin);
    int n;
    std::cin >> n;

    std::vector<int> vct;
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> a[i];
        vct.push_back(a[i]);
    }

    std::sort(vct.begin(), vct.end());
    vct.erase(std::unique(vct.begin(), vct.end()), vct.end());
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> b[i];
        c[i] = std::lower_bound(vct.begin(), vct.end(), a[i]) - vct.begin() + 1;
        t[i].build(vct.size());
    }

    int ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        int max = 0;
        for (int j = 1; j <= n; ++j)
        {
            if (j != 1)
                max = std::max(max, t[j - 1].query(c[i] - 1));
            t[j].modify(c[i], max + (a[i] == b[j]));
            ans = std::max(ans, max + (a[i] == b[j]));
        }
    }

    std::cout << ans << std::endl;
    return 0;
}