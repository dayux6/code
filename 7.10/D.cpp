#include <bits/stdc++.h>

int *t;

int ls(int x) { return x * 2; }

int rs(int x) { return x * 2 + 1; }

void update(int x) { t[x] = std::max(t[ls(x)], t[rs(x)]); }

void modify(int x, int l, int r, int p, int v)
{
    if (l == r)
    {
        t[x] = v;
        return;
    }
    int mid = (l + r) / 2;
    if (p <= mid)
        modify(ls(x), l, mid, p, v);
    else
        modify(rs(x), mid + 1, r, p, v);
    update(x);
}

int query(int x, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr)
        return t[x];
    int mid = (l + r) / 2;
    if (ql > mid)
        return query(rs(x), mid + 1, r, ql, qr);
    else if (qr <= mid)
        return query(ls(x), l, mid, ql, qr);
    else
        return std::max(query(ls(x), l, mid, ql, qr), query(rs(x), mid + 1, r, ql, qr));
}

int main()
{
    freopen("D.in", "r", stdin);
    int m, d;
    std::cin >> m >> d;
    int cnt = 0;
    std::vector<std::pair<char, int>> q;
    for (int i = 0; i < m; ++i)
    {
        char c;
        int v;
        std::cin >> c >> v;
        cnt += c == 'A';
        q.emplace_back(c, v);
    }
    t = new int[cnt * 4]();
    int lst = 0, len = 0;
    for (auto pr : q)
        if (pr.first == 'Q')
            std::cout << (lst = query(1, 1, cnt, len - pr.second + 1, len)) << '\n';
        else
            modify(1, 1, cnt, ++len, (pr.second + lst) % d);
    return 0;
}