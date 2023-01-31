#include <bits/stdc++.h>

const int maxn = 5e5, maxlg = 19;

std::array<int, maxn + 1> a;

class LB
{
private:
    std::array<int, maxlg + 1> v, p;

public:
    LB()
    {
        v.fill(0);
        p.fill(0);
    }

    void ins(int id)
    {
        int x = a[id];
        for (int i = maxlg; i >= 0; --i)
            if ((x >> i) & 1)
            {
                if (p[i] == 0)
                {
                    v[i] = x;
                    p[i] = id;
                    break;
                }
                else if (p[i] < id)
                {
                    std::swap(v[i], x);
                    std::swap(p[i], id);
                }
                x ^= v[i];
            }
    }

    int query(int l)
    {
        int ret = 0;
        for (int i = maxlg; i >= 0; --i)
            if (p[i] >= l)
                ret = std::max(ret, ret ^ v[i]);
        return ret;
    }
};
std::array<LB, maxn + 1> lb;

int main()
{
    std::freopen("CF1100F.in", "r", stdin);

    int n;
    std::cin >> n;

    lb[0] = LB();
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> a[i];
        lb[i] = lb[i - 1];
        lb[i].ins(i);
    }

    int q;
    std::cin >> q;
    for (int i = 0; i < q; ++i)
    {
        int l, r;
        std::cin >> l >> r;
        std::cout << lb[r].query(l) << std::endl;
    }
    return 0;
}