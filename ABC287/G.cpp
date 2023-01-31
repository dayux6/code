#include <bits/stdc++.h>

const int maxn = 2e5, maxs = 1e9;

int s[maxn + 1], c[maxn + 1];

namespace segt
{
    struct node
    {
        int cnt;
        long long sum;
        node *ls, *rs;

        node()
        {
            cnt = sum = 0;
            ls = rs = nullptr;
        }
    } *rt;

    void update(node *x)
    {
        x->cnt = (x->ls == nullptr ? 0 : x->ls->cnt) + (x->rs == nullptr ? 0 : x->rs->cnt);
        x->sum = (x->ls == nullptr ? 0 : x->ls->sum) + (x->rs == nullptr ? 0 : x->rs->sum);
    }

    void modify(node *&x, int l, int r, int p, int v)
    {
        if (x == nullptr)
            x = new node();

        if (l == r)
        {
            x->cnt += v;
            x->sum += 1ll * p * v;
        }
        else
        {
            int mid = (l + r) / 2;

            if (p <= mid)
                modify(x->ls, l, mid, p, v);
            else
                modify(x->rs, mid + 1, r, p, v);

            update(x);
        }
    }

    long long query(node *x, int l, int r, int lim)
    {
        if ((x == nullptr ? 0 : x->cnt) < lim)
            return -1;
        if (l == r)
            return 1ll * lim * l;

        int mid = (l + r) / 2;
        if (lim <= (x->rs == nullptr ? 0 : x->rs->cnt))
            return query(x->rs, mid + 1, r, lim);
        else
            return query(x->ls, l, mid, lim - (x->rs == nullptr ? 0 : x->rs->cnt)) + (x->rs == nullptr ? 0 : x->rs->sum);
    }
};

int main()
{
    std::freopen("G.in", "r", stdin);

    int n;
    std::cin >> n;

    segt::rt = nullptr;
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> s[i] >> c[i];
        segt::modify(segt::rt, 0, maxs, s[i], c[i]);
    }

    int q;
    std::cin >> q;
    for (int i = 0, op, x; i < q; ++i)
    {
        std::cin >> op >> x;

        switch (op)
        {
        case 1:
        {
            segt::modify(segt::rt, 0, maxs, s[x], -c[x]);
            std::cin >> s[x];
            segt::modify(segt::rt, 0, maxs, s[x], c[x]);
            break;
        }

        case 2:
        {
            segt::modify(segt::rt, 0, maxs, s[x], -c[x]);
            std::cin >> c[x];
            segt::modify(segt::rt, 0, maxs, s[x], c[x]);
            break;
        }

        case 3:
            std::cout << segt::query(segt::rt, 0, maxs, x) << '\n';
            break;
        }
    }
    return 0;
}