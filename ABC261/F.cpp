#include <bits/stdc++.h>

class BIT
{
private:
    int n, *t;
    int lowbit(int);

public:
    BIT(int);
    void modify(int, int);
    int query(int);
};

BIT::BIT(int _n) : n(_n), t(new int[_n + 1]()) {}

int BIT::lowbit(int x) { return x & -x; }

void BIT::modify(int x, int v)
{
    for (int i = x; i <= n; i += lowbit(i))
        t[i] += v;
}

int BIT::query(int x)
{
    int ret = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        ret += t[i];
    return ret;
}

int main()
{
    freopen("F.in", "r", stdin);
    int n;
    std::cin >> n;
    std::unordered_map<int, std::vector<int>> ball;
    for (int i = 1; i <= n; ++i)
    {
        int c;
        std::cin >> c;
        ball[c].emplace_back(i);
    }
    int *x = new int[n + 1];
    long long ans = 0;
    BIT t(n);
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> x[i];
        ans += i - 1 - t.query(x[i]);
        t.modify(x[i], 1);
    }
    for (int i = 1; i <= n; ++i)
        t.modify(x[i], -1);
    for (auto pr : ball)
    {
        int cnt = 0;
        for (int i : pr.second)
        {
            ans -= cnt - t.query(x[i]);
            ++cnt;
            t.modify(x[i], 1);
        }
        for (int i : pr.second)
            t.modify(x[i], -1);
    }
    std::cout << ans << std::endl;
    return 0;
}