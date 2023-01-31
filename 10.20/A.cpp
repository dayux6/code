#include <bits/stdc++.h>

const int maxn = 100;

int type[maxn + 1];
char s[maxn + 1];

int main()
{
    std::freopen("A.in", "r", stdin);

    int t;
    std::cin >> t;

    while (t--)
    {
        std::scanf("%s", s + 1);

        int n = std::strlen(s + 1), cnt[4];
        cnt[1] = cnt[2] = cnt[3] = 0;

        for (int i = 1; i <= n; ++i)
        {
            if (std::isdigit(s[i]))
                type[i] = 1;
            if (std::isupper(s[i]))
                type[i] = 2;
            if (std::islower(s[i]))
                type[i] = 3;

            ++cnt[type[i]];
        }

        int c = 0;
        for (int i = 1; i <= 3; ++i)
            if (cnt[i] > 0)
                ++c;

        if (c == 1)
        {
            if (cnt[1] == 0)
                std::cout << rand() % 10;
            if (cnt[2] == 0)
                std::cout << (char)('A' + rand() % 26);
            if (cnt[3] == 0)
                std::cout << (char)('a' + rand() % 26);

            for (int i = 3; i <= n; ++i)
                std::cout << s[i];
            std::cout << std::endl;
        }
        else if (c == 2)
        {
            bool flg = false;
            for (int i = 1; i <= n; ++i)
            {
                if (!flg && cnt[type[i]] > 1)
                {
                    flg = true;

                    if (cnt[1] == 0)
                        std::cout << rand() % 10;
                    else if (cnt[2] == 0)
                        std::cout << (char)('A' + rand() % 26);
                    else
                        std::cout << (char)('a' + rand() % 26);
                }
                else
                    std::cout << s[i];
            }

            std::cout << std::endl;
        }
        else
            std::printf("%s\n", s + 1);
    }
    return 0;
}