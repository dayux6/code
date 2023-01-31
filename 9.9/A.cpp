#include <bits/stdc++.h>

typedef long double db;

const int maxn = 10;

int i;
db r[maxn + 1];
std::string s;

db solve()
{
    ++i;
    int type = -1;
    db pre = 0;
    for (; i < s.size(); ++i)
        if (isdigit(s.at(i)))
            switch (type)
            {
            case -1:
                pre = r[s.at(i) - '0'];
                break;
            case 0:
                pre += r[s.at(i) - '0'];
                break;
            case 1:
                pre += 1 / r[s.at(i) - '0'];
                break;
            }
        else if (s.at(i) == '-')
            type = 0;
        else if (s.at(i) == '|')
        {
            if (type == -1)
                pre = 1 / pre;
            type = 1;
        }
        else if (s.at(i) == '(')
        {
            switch (type)
            {
            case -1:
                pre = solve();
                break;
            case 0:
                pre += solve();
                break;
            case 1:
                pre += 1 / solve();
                break;
            }
        }
        else if (s.at(i) == ')')
        {
            if (type == 1)
                return 1 / pre;
            else
                return pre;
        }
}

int main()
{
    freopen("A.in", "r", stdin);
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
        std::cin >> r[i];

    std::cin >> std::ws;
    std::string tmp;
    while (!std::cin.eof())
    {
        std::cin >> tmp >> std::ws;
        s += tmp;
    }

    std::cout << std::fixed << std::setprecision(5) << solve() << std::endl;
    return 0;
}