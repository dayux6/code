#include <bits/stdc++.h>

const int maxn = 1e3, maxlg = 60;

std::pair<long long, int> pr[maxn];

class LB
{
private:
    int n;
    long long lb[maxlg];

public:
    LB(int);
    bool ins(long long);
};

LB::LB(int _n) : n(_n) { std::fill_n(lb, _n, 0); }

bool LB::ins(long long x)
{
    for (int i = n - 1; i >= 0; --i)
        if ((x >> i) & 1)
        {
            if (lb[i])
                x ^= lb[i];
            else
            {
                lb[i] = x;
                return true;
            }
        }
    return false;
}

int main()
{
    freopen("P4570.in", "r", stdin);
    int n;
    std::cin >> n;
    long long max = 0;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> pr[i].first >> pr[i].second;
        max = std::max(max, pr[i].first);
    }

    std::sort(pr, pr + n, [](std::pair<long long, int> x, std::pair<long long, int> y)
              { return x.second > y.second; });
    int sum = 0;
    LB lb(log2(max) + 1);
    for (int i = 0; i < n; ++i)
        if (lb.ins(pr[i].first))
            sum += pr[i].second;

    std::cout << sum << std::endl;
    return 0;
}