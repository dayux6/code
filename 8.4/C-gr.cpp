#include <bits/stdc++.h>

const int maxn = 2e5;

int p[maxn + 1], c[maxn + 1];
bool flg[maxn + 1];

int main()
{
    freopen("C.in", "r", stdin);
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
        std::cin >> p[i];
    for (int i = 1; i <= n; ++i)
        std::cin >> c[i];

    std::deque<int> vct;
    for (int i = 1; i <= n; ++i)
        vct.push_back(i);
    std::sort(vct.begin(), vct.end(), [=](int x, int y)
              { int cntx = 0; for (int i = 1; i < x; ++i) if (!flg[i]) cntx += p[i] > p[x]; for (int i = x + 1; i <= n; ++i)if (!flg[i]) cntx += p[i] < p[x]; int cnty = 0; for (int i = 1; i < y; ++i)if (!flg[i]) cnty += p[i] > p[y]; for (int i = y + 1; i <= n; ++i) if (!flg[i]) cnty += p[i] < p[y]; return c[x] * cnty < c[y] * cntx; });

    int ans = 0;
    while (!vct.empty())
    {
        int x = vct.front();
        vct.pop_front();
        if (!flg[x])
        {
            ans += c[x];
            for (int i = 1; i < x; ++i)
                if (p[i] > p[x])
                    flg[i] = true;
            for (int i = x + 1; i <= n; ++i)
                if (p[i] < p[x])
                    flg[i] = true;
        }
        std::sort(vct.begin(), vct.end(), [=](int x, int y)
                  { int cntx = 0; for (int i = 1; i < x; ++i) if (!flg[i]) cntx += p[i] > p[x]; for (int i = x + 1; i <= n; ++i)if (!flg[i]) cntx += p[i] < p[x]; int cnty = 0; for (int i = 1; i < y; ++i)if (!flg[i]) cnty += p[i] > p[y]; for (int i = y + 1; i <= n; ++i) if (!flg[i]) cnty += p[i] < p[y]; return c[x] * cnty < c[y] * cntx; });
    }
    std::cout << ans << std::endl;
    return 0;
}