#include <bits/stdc++.h>

typedef long long ll;

const int maxs = 50;

class LB
{
private:
    ll a[maxs + 1];

public:
    LB();
    void ins(ll);
    ll getmax();
};

LB::LB() { std::fill_n(a, maxs + 1, 0); }

void LB::ins(ll x)
{
    for (int i = maxs; i >= 0; --i)
        if ((x >> i) & 1)
            if (a[i])
                x ^= a[i];
            else
            {
                a[i] = x;
                break;
            }
}

ll LB::getmax()
{
    ll ret = 0;
    for (int i = maxs; i >= 0; --i)
        ret = std::max(ret, ret ^ a[i]);
    return ret;
}

int main()
{
    int n;
    std::cin >> n;
    LB lb;
    for (int i = 0; i < n; ++i)
    {
        ll a;
        std::cin >> a;

        lb.ins(a);
    }

    std::cout << lb.getmax() << std::endl;
    return 0;
}