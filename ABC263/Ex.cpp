#include <bits/stdc++.h>

typedef long double db;

const int maxn = 5e4;
const db eps = 1e-6, pi = acos(-1);

struct line
{
    db a, b, c;
} l[maxn + 1];

class BIT
{
private:
    int n, t[maxn * 2 + 1];
    int lowbit(int x) { return x & -x; }

public:
    BIT(int _n) : n(_n) {}

    void clear() { std::fill_n(t + 1, n, 0); }

    void modify(int x, int v)
    {
        for (int i = x; i <= n; i += lowbit(i))
            t[i] += v;
    }

    int query(int x)
    {
        int ret = 0;
        for (int i = x; i; i -= lowbit(i))
            ret += t[i];
        return ret;
    }

    int query(int l, int r) { return query(r) - query(l - 1); }
};

int main()
{
    freopen("Ex.in", "r", stdin);
    int n, k;
    std::cin >> n >> k;

    for (int i = 1; i <= n; ++i)
        std::cin >> l[i].a >> l[i].b >> l[i].c;

    db now = 0, tmp = 1e-4;
    BIT t(n * 2);
    while (tmp >= 1e-6)
    {
        db mid = now + tmp;

        std::vector<db> vct;
        std::vector<std::pair<int, int>> p;
        std::vector<std::pair<db, db>> ang;
        for (int i = 1; i <= n; ++i)
        {
            db dis = std::abs(l[i].c) / hypot(l[i].a, l[i].b);

            if (dis == 0)
            {
                db angx = atan2(l[i].a * mid / hypot(l[i].a, l[i].b), -l[i].b * mid / hypot(l[i].a, l[i].b)), angy = atan2(-l[i].a * mid / hypot(l[i].a, l[i].b), l[i].b * mid / hypot(l[i].a, l[i].b));

                if (angx > angy)
                    std::swap(angx, angy);

                ang.emplace_back(angx, angy);
                vct.push_back(angx);
                vct.push_back(angy);
            }
            else if (dis <= mid)
            {
                db base = atan2(-l[i].b * l[i].c / (l[i].a * l[i].a + l[i].b * l[i].b), -l[i].a * l[i].c / (l[i].a * l[i].a + l[i].b * l[i].b)), angx = base - acos(dis / mid), angy = base + acos(dis / mid);

                if (angx < -pi)
                    angx += pi * 2;
                else if (angx > pi)
                    angx -= pi * 2;
                if (angy < -pi)
                    angy += pi * 2;
                else if (angy > pi)
                    angy -= pi * 2;

                if (angx > angy)
                    std::swap(angx, angy);

                ang.emplace_back(angx, angy);
                vct.push_back(angx);
                vct.push_back(angy);
            }
        }

        std::sort(vct.begin(), vct.end());
        for (std::pair<db, db> pr : ang)
            p.emplace_back(std::lower_bound(vct.begin(), vct.end(), pr.first) - vct.begin() + 1, std::lower_bound(vct.begin(), vct.end(), pr.second) - vct.begin() + 1);

        std::sort(p.begin(), p.end());
        t.clear();
        int cnt = 0;
        for (std::pair<int, int> pr : p)
        {
            cnt += t.query(pr.first, pr.second);
            t.modify(pr.second, 1);
        }

        if (cnt < k)
        {
            now += tmp;
            tmp *= 2;
        }
        else
            tmp /= 2;
    }
    std::cout << std::fixed << now << std::endl;
    return 0;
}