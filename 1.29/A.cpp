#include <bits/stdc++.h>
#include <bits/extc++.h>

const int maxn = 1e5, maxlg = 16;

int n, max[maxn][maxlg + 1], L[maxn], R[maxn];

class segt
{
private:
    int cnt[maxn * 4], add[maxn * 4];
    bool tag[maxn * 4];

    inline int ls(int x) { return x * 2; }
    inline int rs(int x) { return x * 2 + 1; }
    inline void update(int x) { tag[x] = tag[ls(x)] & tag[rs(x)]; }

    inline void pushup(int x, int v)
    {
        if (!tag[x])
        {
            cnt[x] += v;
            add[x] += v;
        }
    }

    inline void pushdown(int x)
    {
        if (!tag[x] && add[x] != 0)
        {
            pushup(ls(x), add[x]);
            pushup(rs(x), add[x]);
            add[x] = 0;
        }
    }

    void modify(int x, int l, int r, int ql, int qr, int v)
    {
        if (tag[x])
            return;

        if (ql <= l && r <= qr)
        {
            pushup(x, v);
            return;
        }

        pushdown(x);
        int mid = (l + r) / 2;
        if (ql <= mid)
            modify(ls(x), l, mid, ql, qr, v);
        if (qr > mid)
            modify(rs(x), mid + 1, r, ql, qr, v);
    }

    void modify(int x, int l, int r, int ql, int qr)
    {
        if (tag[x])
            return;

        if (l != r)
            pushdown(x);
        if (ql <= l && r <= qr)
        {
            tag[x] = true;
            return;
        }

        int mid = (l + r) / 2;
        if (ql <= mid)
            modify(ls(x), l, mid, ql, qr);
        if (qr > mid)
            modify(rs(x), mid + 1, r, ql, qr);

        update(x);
    }

    int query(int x, int l, int r, int p)
    {
        if (l == r)
            return cnt[x];
        else
        {
            pushdown(x);
            int mid = (l + r) / 2;
            if (p <= mid)
                return query(ls(x), l, mid, p);
            else
                return query(rs(x), mid + 1, r, p);
        }
    }

public:
    segt()
    {
        std::fill_n(cnt, n * 4, 0);
        std::fill_n(add, n * 4, 0);
        std::fill_n(tag, n * 4, false);
    }

    void modify(int l, int r, int v) { modify(1, 1, n, l, r, v); }
    void modify(int l, int r) { modify(1, 1, n, l, r); }
    int query(int p) { return query(1, 1, n, p); }
} t;

int main()
{
    std::freopen("tournament.in", "r", stdin);
    std::freopen("tournament.out", "w", stdout);

    int c, w;
    std::cin >> n >> c >> w;

    for (int i = 1; i < n; ++i)
        std::cin >> max[i][0];
    for (int i = 1; i <= maxlg; ++i)
        for (int j = 1; j + (1 << i) < n; ++j)
            max[j][i] = std::max(max[j][i - 1], max[j + (1 << (i - 1))][i - 1]);

    auto query = [&](int l, int r)
    {
        int k = std::log2(r - l + 1);
        return std::max(max[l][k], max[r - (1 << k) + 1][k]);
    };

    __gnu_pbds::tree<int, __gnu_pbds::null_type, std::less<int>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> tl, tr;
    for (int i = 1; i <= n; ++i)
    {
        tl.insert(i);
        tr.insert(i);
    }

    for (int i = 0, l, r; i < c; ++i)
    {
        std::cin >> l >> r;

        auto itl = tl.find_by_order(l), itr = tl.find_by_order(r + 1);
        L[i] = *itl;
        for (auto it = std::next(itl); it != itr;)
            it = tl.erase(it);

        itl = tr.find_by_order(l);
        itr = tr.find_by_order(r);
        R[i] = *itr;
        for (auto it = itl; it != itr;)
            it = tr.erase(it);
    }

    for (int i = 0; i < c; ++i)
    {
        if (query(L[i], R[i] - 1) > w)
            t.modify(L[i], R[i]);
        else
            t.modify(L[i], R[i], 1);
    }

    int max = t.query(1), pos = 1;
    for (int i = 2, tmp; i <= n; ++i)
    {
        tmp = t.query(i);

        if (max < tmp)
        {
            max = tmp;
            pos = i;
        }
    }

    std::cout << pos - 1 << std::endl;
    return 0;
}