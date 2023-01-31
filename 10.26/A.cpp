#include <bits/stdc++.h>

const int maxn = 9;

typedef long double db;

int p;
db r[maxn + 1];
std::string s;

db solve()
{
    int op = -1;
    db fir, ret = 0;
    while (p < s.size())
    {
        switch (s.at(p))
        {
        case 'R':
        {
            ++p;
            if (op == 1)
                ret += 1 / r[s.at(p) - '0'];
            else if (op == 0)
                ret += r[s.at(p) - '0'];
            else
                fir = r[s.at(p) - '0'];
            break;
        }
        case '-':
        {
            if (op == -1)
            {
                ret = fir;
                op = 0;
            }
            break;
        }
        case '|':
        {
            if (op == -1)
            {
                ret = 1 / fir;
                op = 1;
            }
            break;
        }
        case '(':
        {
            ++p;
            if (op == 1)
                ret += 1 / solve();
            else if (op == 0)
                ret += solve();
            else
                fir = solve();
            break;
        }
        case ')':
        {
            if (op == 1)
                return 1 / ret;
            else if (op == 0)
                return ret;
            break;
        }
        }
        ++p;
    }
    return fir;
}

int main()
{
    std::freopen("resistance.in", "r", stdin);
    std::freopen("resistance.out", "w", stdout);

    int n;
    std::cin >> n;

    for (int i = 1; i <= n; ++i)
        std::cin >> r[i];

    std::cin >> std::ws;
    while (!std::cin.eof())
    {
        std::string tmp;
        std::cin >> tmp >> std::ws;
        s.append(tmp);
    }

    std::cout << std::fixed << std::setprecision(5) << solve() << std::endl;
    return 0;
}