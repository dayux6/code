#include <bits/stdc++.h>

const int maxQ = 1e5;

int ans[maxQ];

struct query
{
    int no, x, k;

    query() { std::cin >> x >> k; }
};

struct node
{
    int cnt;
    node *s[2];

    node() : cnt(0) { s[0] = s[1] = nullptr; }
} * rt;

int getsiz(node *x)
{
    if (x == nullptr)
        return 0;
    else
        return x->cnt;
}

node *merge(node *x, node *y)
{
    if (x == nullptr)
        return y;
    if (y == nullptr)
        return x;

    node *ret = new node;

    ret->s[0] = merge(x->s[0], y->s[0]);
    ret->s[1] = merge(x->s[1], y->s[1]);
    ret->cnt = getsiz(x) + getsiz(y);
    return ret;
}

void insert(int x)
{
    node *cur = rt;
    ++cur->cnt;
    for (int i = 17; i >= 0; --i)
    {
        bool k = (x >> i) & 1;

        if (cur->s[k] == nullptr)
            cur->s[k] = new node();
        cur = cur->s[k];
        ++cur->cnt;
    }
}

void solve(int d, node *x, int v, std::vector<query> vq)
{
    if (d == -1)
    {
        for (query q : vq)
            ans[q.no] = v;
        return;
    }

    std::vector<query> ql, qr, q0;
    for (query q : vq)
        if ((q.x >> d) & 1)
            if (q.k <= getsiz(x->s[0]))
                ql.push_back(q);
            else
            {
                q.k -= getsiz(x->s[0]);
                qr.push_back(q);
            }
        else
            q0.push_back(q);

    if (!ql.empty())
        solve(d - 1, x->s[0], v * 2, ql);
    if (!qr.empty())
        solve(d - 1, x->s[1], v * 2 + 1, qr);
    if (!q0.empty())
        solve(d - 1, merge(x->s[0], x->s[1]), v * 2, q0);
}

int main()
{
    freopen("D.in", "r", stdin);
    int n;
    std::cin >> n;

    rt = new node();
    for (int i = 0; i < n; ++i)
    {
        int a;
        std::cin >> a;
        insert(a);
    }

    int Q;
    std::cin >> Q;
    std::vector<query> q;
    for (int i = 0; i < Q; ++i)
    {
        q.emplace_back();
        q.back().k = n - q.back().k + 1;
        q.back().no = i;
    }

    solve(17, rt, 0, q);

    for (int i = 0; i < Q; ++i)
        std::cout << ans[i] << std::endl;
    return 0;
}