#include <bits/stdc++.h>

const int maxn = 50, maxm = 50;

char str[maxn];

class LB
{
private:
    int n;
    long long lb[maxn + 1];

public:
    LB(int);
    void ins(long long);
    int size();
};

LB::LB(int _n) : n(_n) { std::fill_n(lb, n, 0); }

void LB::ins(long long x)
{
    for (int i = n - 1; i >= 0; --i)
        if ((x >> i) & 1)
        {
            if (!lb[i])
            {
                lb[i] = x;
                break;
            }
            else
                x ^= lb[i];
        }
}

int LB::size()
{
    int ret = 0;
    for (int i = 0; i < n; ++i)
        if (lb[i])
            ++ret;
    return ret;
}

int main()
{
    freopen("P3857.in", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);
    LB lb(n);
    for (int i = 0; i < m; ++i)
    {
        scanf("%s", str);
        long long tmp = 0;
        for (int j = 0; j < n; ++j)
            if (str[j] == 'O')
                tmp |= 1ll << j;
        lb.ins(tmp);
    }
    std::cout << (1ll << lb.size()) % 2008 << std::endl;
    return 0;
}