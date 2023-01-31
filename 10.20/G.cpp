#include <bits/stdc++.h>

const int maxn = 2e5;

int n, lim[maxn * 2 + 1];
long long ans;

class DSU
{
private:
    int fa[maxn * 2 + 1];

public:
    DSU() { std::iota(fa + 1, fa + maxn * 2 + 1, 1); }

    int find(int x)
    {
        while (x != fa[x])
            x = fa[x] = fa[fa[x]];
        return x;
    }

    void merge(int x, int y) { fa[find(y)] = find(x); }
} dsu;

class segt
{
private:
    struct node
    {
        int c;
        long long s;
        node *ls, *rs;

        node() : c(0), s(0), ls(nullptr), rs(nullptr) {}
    };

    void update(node *x)
    {
        x->c = x->s = 0;
        if (x->ls != nullptr)
        {
            x->c += x->ls->c;
            x->s += x->ls->s;
        }
        if (x->rs != nullptr)
        {
            x->c += x->rs->c;
            x->s += x->rs->s;
        }
        if (x->ls != nullptr && x->rs != nullptr)
            ans += x->ls->s * x->rs->c;
    }

    node *merge(node *x, node *y, int l, int r)
    {
        if (x == nullptr)
            return y;
        if (y == nullptr)
            return x;

        if (x->ls != nullptr && x->rs != nullptr)
            ans -= x->ls->s * x->rs->c;
        if (y->ls != nullptr && y->rs != nullptr)
            ans -= y->ls->s * y->rs->c;

        int mid = (l + r) / 2;
        node *ret = new node();
        ret->ls = merge(x == nullptr ? nullptr : x->ls, y == nullptr ? nullptr : y->ls, l, mid);
        ret->rs = merge(x == nullptr ? nullptr : x->rs, y == nullptr ? nullptr : y->rs, mid + 1, r);
        update(ret);
        return ret;
    }

public:
    std::array<node *, maxn * 2 + 1> rt;

    segt() { rt.fill(nullptr); }

    void modify(node *&x, int l, int r, int p)
    {
        if (x == nullptr)
            x = new node();

        if (l == r)
        {
            x->c = 1;
            x->s = p;
        }
        else
        {
            int mid = (l + r) / 2;
            if (p <= mid)
                modify(x->ls, l, mid, p);
            else
                modify(x->rs, mid + 1, r, p);
            update(x);
        }
    }

    void merge(int x, int y)
    {
        x = dsu.find(x);
        y = dsu.find(y);
        dsu.merge(x, y);
        lim[x] = lim[y];
        ans -= x * rt[x]->s + y * rt[y]->s;
        rt[x] = merge(rt[x], rt[y], 1, n);
        ans += x * rt[x]->s;
    }
};

int main()
{
    std::freopen("G.in", "r", stdin);

    std::cin >> n;

    std::iota(lim + 1, lim + maxn * 2 + 1, 1);

    segt t;
    for (int i = 1; i <= n; ++i)
    {
        int a, b;
        std::cin >> a >> b;

        int p = t.rt[dsu.find(a)] == nullptr ? a : lim[dsu.find(a)] + 1;
        ans += 1ll * (p - a) * b;
        t.modify(t.rt[p], 1, n, b);

        if (t.rt[p - 1] != nullptr)
            t.merge(p - 1, p);
        if (t.rt[p + 1] != nullptr)
            t.merge(p, p + 1);

        std::cout << ans << std::endl;
    }
    return 0;
}