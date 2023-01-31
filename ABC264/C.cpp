#include <bits/stdc++.h>

const int maxn = 10, maxm = 10;

int a[maxn][maxn], b[maxn][maxn];

int main()
{
    int n1, m1;
    std::cin >> n1 >> m1;
    for (int i = 0; i < n1; ++i)
        for (int j = 0; j < m1; ++j)
            std::cin >> a[i][j];

    int n2, m2;
    std::cin >> n2 >> m2;
    for (int i = 0; i < n2; ++i)
        for (int j = 0; j < m2; ++j)
            std::cin >> b[i][j];

    for (int Sr = 0; Sr < (1 << n1); ++Sr)
        if (__builtin_popcount(Sr) == n2)
            for (int Sc = 0; Sc < (1 << m1); ++Sc)
                if (__builtin_popcount(Sc) == m2)
                {
                    int r = 0;
                    bool flg = true;
                    for (int i = 0; i < n1; ++i)
                        if ((Sr >> i) & 1)
                        {
                            int c = 0;
                            for (int j = 0; j < m1; ++j)
                                if ((Sc >> j) & 1)
                                {
                                    if (a[i][j] != b[r][c])
                                    {
                                        flg = false;
                                        break;
                                    }
                                    ++c;
                                }
                            if (!flg)
                                break;
                            ++r;
                        }
                    if (flg)
                    {
                        std::cout << "Yes" << std::endl;
                        return 0;
                    }
                }
    std::cout << "No" << std::endl;
    return 0;
}