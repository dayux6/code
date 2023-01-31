#include <bits/stdc++.h>

const int maxxy = 1e4;

bool fx[maxxy * 2 + 1][2], fy[maxxy * 2 + 1][2];

int main()
{
    std::freopen("D.in", "r", stdin);

    int n, a, x, y;
    std::cin >> n >> x >> y >> a;

    bool kx = 1, ky = 1;
    fx[maxxy + a][0] = true;
    fy[maxxy][0] = true;

    for (int i = 2; i <= n; ++i)
    {
        std::cin >> a;

        if (i & 1)
        {
            for (int j = 0; j <= maxxy * 2; ++j)
                fx[j][kx] = false;
            for (int j = 0; j <= maxxy * 2; ++j)
                if (fx[j][kx ^ 1])
                {
                    if (j - a >= 0)
                        fx[j - a][kx] = true;
                    if (j + a <= maxxy * 2)
                        fx[j + a][kx] = true;
                }
            kx ^= 1;
        }
        else
        {
            for (int j = 0; j <= maxxy * 2; ++j)
                fy[j][ky] = false;
            for (int j = 0; j <= maxxy * 2; ++j)
                if (fy[j][ky ^ 1])
                {
                    if (j - a >= 0)
                        fy[j - a][ky] = true;
                    if (j + a <= maxxy * 2)
                        fy[j + a][ky] = true;
                }
            ky ^= 1;
        }
    }

    if (fx[maxxy + x][kx ^ 1] && fy[maxxy + y][ky ^ 1])
        std::cout << "Yes" << std::endl;
    else
        std::cout << "No" << std::endl;
    return 0;
}