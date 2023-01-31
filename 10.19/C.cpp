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

const int maxn = 2e5;

int k, sum[maxn + 1], l[maxn + 1], r[maxn + 1];
long long a[maxn + 1];

class CMT
{
private:
    struct node
    {
        int cnt;
        node *ls, *rs;

        node() : cnt(0), ls(nullptr), rs(nullptr) {}
    };
    std::vector<node *> rt;

    void modify(node *&x, int l, int r, int p, node *pre)
    {
        if (x == nullptr)
        {
            x = new node();
            x->cnt = pre == nullptr ? 0 : pre->cnt;
        }
        ++x->cnt;

        if (l != r)
        {
            int mid = (l + r) / 2;

            if (p <= mid)
            {
                modify(x->ls, l, mid, p, pre == nullptr ? nullptr : pre->ls);
                x->rs = pre == nullptr ? nullptr : pre->rs;
            }
            else
            {
                x->ls = pre == nullptr ? nullptr : pre->ls;
                modify(x->rs, mid + 1, r, p, pre == nullptr ? nullptr : pre->rs);
            }
        }
    }

    int query(node *x, node *y, int l, int r, int p)
    {
        if (y == nullptr)
            return 0;

        if (l == r)
            return y->cnt - (x == nullptr ? 0 : x->cnt);

        int mid = (l + r) / 2;
        if (p <= mid)
            return query(x == nullptr ? nullptr : x->ls, y->ls, l, mid, p);
        else
            return query(x == nullptr ? nullptr : x->rs, y->rs, mid + 1, r, p);
    }

public:
    CMT()
    {
        rt.push_back(nullptr);
        modify(rt.back(), 0, k - 1, 0, nullptr);
    }

    void modify(int p)
    {
        rt.push_back(nullptr);
        modify(rt.back(), 0, k - 1, p, rt.at(rt.size() - 2));
    }

    int query(int l, int r, int p)
    {
        if (l <= r)
            return query(l == 0 ? nullptr : rt.at(l - 1), rt.at(r), 0, k - 1, p);
        else
            return 0;
    }
};

int main()
{
    std::freopen("interval.in", "r", stdin);
    std::freopen("interval.out", "w", stdout);

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    read(n);
    read(k);

    CMT t;
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        sum[i] = (sum[i - 1] + a[i] % k) % k;
        t.modify(sum[i]);
    }

    std::stack<int> s;
    for (int i = 1; i <= n; ++i)
    {
        while (!s.empty() && a[i] >= a[s.top()])
            s.pop();
        l[i] = s.empty() ? 0 : s.top();
        s.push(i);
    }

    while (!s.empty())
        s.pop();
    for (int i = n; i >= 1; --i)
    {
        while (!s.empty() && a[i] > a[s.top()])
            s.pop();
        r[i] = s.empty() ? n + 1 : s.top();
        s.push(i);
    }

    long long ans = 0;
    for (int i = 1; i <= n; ++i)
        if (i - l[i] < r[i] - i)
            for (int j = l[i]; j < i; ++j)
                ans += t.query(std::max(j + 2, i), r[i] - 1, (sum[j] + a[i] % k) % k);
        else
            for (int j = i; j < r[i]; ++j)
                ans += t.query(l[i], std::min(j - 2, i - 1), ((sum[j] - a[i] % k) % k + k) % k);

    std::cout << ans << std::endl;
    return 0;
}