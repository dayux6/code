#include <bits/stdc++.h>

const int maxn = 937500;

unsigned int inc[maxn + 1], dec[maxn + 1];

int main()
{
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
    int n, t;
    std::cin >> n >> t >> t >> t;

    std::set<int> s;
    int cnt = 0;
    for (int i = 0; i < n; ++i)
    {
        int op;
        std::cin >> op;
        switch (op)
        {
        case 1:
        {
            int a, b;
            std::cin >> a >> b;

            int p = b / 32, q = b % 32;
            if (a > 0)
            {
                unsigned int st = (unsigned int)a << q, pro = (unsigned int)a >> (31 - q);
                pro >>= 1;
                unsigned int old = inc[p];
                inc[p] += st;
                pro += (old > inc[p]);
                if (inc[p] ^ dec[p])
                    s.insert(p);
                else if (s.count(p))
                    s.erase(p);
                p++;
                while (pro != 0)
                {
                    old = inc[p];
                    inc[p] += pro;
                    pro = (old > inc[p]);
                    if (inc[p] ^ dec[p])
                        s.insert(p);
                    else if (s.count(p))
                        s.erase(p);
                    p++;
                }
            }
            else if (a < 0)
            {
                a = -a;
                unsigned int st = (unsigned int)a << q, pro = (unsigned int)a >> (31 - q);
                pro >>= 1;
                unsigned int old = dec[p];
                dec[p] += st;
                pro += (old > dec[p]);
                if (inc[p] ^ dec[p])
                    s.insert(p);
                else if (s.count(p))
                    s.erase(p);
                p++;
                while (pro != 0)
                {
                    old = dec[p];
                    dec[p] += pro;
                    pro = (old > dec[p]);
                    if (inc[p] ^ dec[p])
                        s.insert(p);
                    else if (s.count(p))
                        s.erase(p);
                    p++;
                }
            }
            break;
        }

        case 2:
        {
            int k;
            std::cin >> k;

            ++cnt;
            auto it = s.empty() ? s.begin() : --s.lower_bound(k / 32);
            if (!s.empty() && it != --s.begin() && inc[*it] < dec[*it])
                std::cout << ((((unsigned int)(inc[k / 32] - 1) - dec[k / 32]) >> (k % 32)) & 1) << std::endl;
            else
                std::cout << (((inc[k / 32] - dec[k / 32]) >> (k % 32)) & 1) << std::endl;
            break;
        }
        }
    }
    return 0;
}