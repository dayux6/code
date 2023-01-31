#include <bits/stdc++.h>

int main()
{
    freopen("B.in", "r", stdin);
    std::string s;
    std::cin >> s;

    if (s.front() == '1')
        std::cout << "No" << std::endl;
    else
    {
        bool flg[7], all[7];
        all[0] = s.at(6) == '1';
        all[1] = s.at(3) == '1';
        all[2] = (s.at(1) == '1') || (s.at(7) == '1');
        all[3] = (s.at(0) == '1') || (s.at(4) == '1');
        all[4] = (s.at(2) == '1') || (s.at(8) == '1');
        all[5] = s.at(5) == '1';
        all[6] = s.at(9) == '1';

        for (int i = 0; i < 7; ++i)
            for (int j = i + 2; j < 7; ++j)
                if (all[i] && all[j])
                    for (int k = i + 1; k < j; ++k)
                        if (!all[k])
                        {
                            std::cout << "Yes" << std::endl;
                            return 0;
                        }

        std::cout << "No" << std::endl;
    }
    return 0;
}