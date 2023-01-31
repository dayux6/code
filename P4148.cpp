#include <bits/stdc++.h>

void chkmin(int &x, int y)
{
    if (x > y)
        x = y;
}

void chkmax(int &x, int y)
{
    if (x < y)
        x = y;
}

struct point
{
    int x, y;

    point() {}
    point(int _x, int _y) : x(_x), y(_y) {}
};

class kDT
{
private:
    const double alpha = 0.75;

    int rt, tot;

    struct node
    {
        int val, sum, lim, ls, rs, siz, minx, miny, maxx, maxy;
        point p;

        node() {}
        node(point x, int _val) : val(_val), sum(_val), ls(0), rs(0), siz(1), minx(x.x), miny(x.y), maxx(x.x), maxy(x.y) { p = x; }
    };
    std::vector<node> t;
    std::vector<std::pair<node, int>> tmp;

    bool isbal(int x) { return alpha * t.at(x).siz <= std::min(t.at(t.at(x).ls).siz, t.at(t.at(x).rs).siz); }

    void update(int x)
    {
        t.at(x).sum = t.at(t.at(x).ls).sum + t.at(x).val + t.at(t.at(x).rs).sum;
        t.at(x).siz = t.at(t.at(x).ls).siz + 1 + t.at(t.at(x).rs).siz;
        chkmin(t.at(x).minx, std::min(t.at(t.at(x).ls).minx, t.at(t.at(x).rs).minx));
        chkmin(t.at(x).miny, std::min(t.at(t.at(x).ls).miny, t.at(t.at(x).rs).miny));
        chkmax(t.at(x).maxx, std::max(t.at(t.at(x).ls).maxx, t.at(t.at(x).rs).maxx));
        chkmax(t.at(x).maxy, std::max(t.at(t.at(x).ls).maxy, t.at(t.at(x).rs).maxy));
    }

    void destroy(int x)
    {
        if (!x)
            return;

        destroy(t.at(x).ls);
        tmp.emplace_back(t.at(x), x);
        destroy(t.at(x).rs);
    }

    int build(int l, int r, bool d)
    {
        int mid = (l + r) / 2;

        std::nth_element(tmp.begin() + l, tmp.begin() + mid, tmp.begin() + r + 1, [=](std::pair<node, int> x, std::pair<node, int> y)
                         { return d ? x.first.p.y < y.first.p.y : x.first.p.x < y.first.p.x; });
        t[tmp.at(mid).second] = node(tmp.at(mid).first.p, tmp.at(mid).first.val);
        t[tmp.at(mid).second].ls = build(l, mid - 1, d ^ 1);
        t[tmp.at(mid).second].rs = build(mid + 1, r, d ^ 1);
        update(tmp.at(mid).second);
        return tmp.at(mid).second;
    }

    void rebuild(int &x, bool d)
    {
        tmp.clear();
        destroy(x);
        x = build(0, tmp.size() - 1, d);
    }

    void modify(int &x, point p, int v, bool d = 0)
    {
        if (!x)
        {
            ++tot;
            x = tot;
            t.emplace_back(node(p, v));
            t.back().lim = d ? p.y : p.x;
            return;
        }

        if (t.at(x).p.x == p.x && t.at(x).p.y == p.y)
            t.at(x).val += v;
        else if (d)
            if (p.y < t.at(x).p.y)
                modify(t.at(x).ls, p, v, d ^ 1);
            else
                modify(t.at(x).rs, p, v, d ^ 1);
        else if (p.x < t.at(x).p.x)
            modify(t.at(x).ls, p, v, d ^ 1);
        else
            modify(t.at(x).rs, p, v, d ^ 1);
        update(x);

        if (isbal(x))
            rebuild(x, d);
    }

    int query(int x, int x1, int y1, int x2, int y2)
    {
        if (!x || x2 < t.at(x).minx || x1 > t.at(x).maxx || y2 < t.at(x).miny || y1 > t.at(x).maxy)
            return 0;
        if (x1 <= t.at(x).minx && x2 >= t.at(x).maxx && y1 <= t.at(x).miny && y2 >= t.at(x).maxy)
            return t.at(x).sum;

        int ret;
        if (t.at(x).p.x >= x1 && t.at(x).p.x <= x2 && t.at(x).p.y >= y1 && t.at(x).p.y <= y2)
            ret = t.at(x).val;
        else
            ret = 0;

        return ret + query(t.at(x).ls, x1, y1, x2, y2) + query(t.at(x).rs, x1, y1, x2, y2);
    }

public:
    kDT() : rt(0), tot(0)
    {
        node x;
        x.val = x.sum = x.ls = x.rs = x.siz = 0;
        x.minx = x.miny = INT_MAX;
        x.maxx = x.maxx = 0;
        t.push_back(x);
    }

    void modify(int x, int y, int v) { modify(rt, point(x, y), v); }

    int query(int x1, int y1, int x2, int y2) { return query(rt, x1, y1, x2, y2); }
};

int main()
{
    freopen("P4148.in", "r", stdin);
    int n;
    std::cin >> n;

    int ans = 0;
    kDT t;
    while (true)
    {
        int op;
        std::cin >> op;

        if (op == 3)
            break;
        switch (op)
        {
        case 1:
        {
            int x, y, v;
            std::cin >> x >> y >> v;
            x ^= ans;
            y ^= ans;
            v ^= ans;
            t.modify(x, y, v);
            break;
        }

        case 2:
        {
            int x1, y1, x2, y2;
            std::cin >> x1 >> y1 >> x2 >> y2;
            x1 ^= ans;
            y1 ^= ans;
            x2 ^= ans;
            y2 ^= ans;
            ans = t.query(x1, y1, x2, y2);
            std::cout << ans << std::endl;
            break;
        }
        }
    }
    return 0;
}