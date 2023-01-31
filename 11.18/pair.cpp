#include <bits/stdc++.h>

void read(int &x)
{
    x = 0;
    char c = std::getchar();

    while (!std::isdigit(c))
        c = std::getchar();
    while (std::isdigit(c))
    {
        x = x * 10 + (c ^ 48);
        c = std::getchar();
    }
}

void chkmax(int &x, int y)
{
    if (x < y)
        x = y;
}

int hmax[2][256][513], lmax[2][256][256][512];

int main()
{
    std::freopen("pair.in", "r", stdin);
    std::freopen("pair.out", "w", stdout);

    int n;
    read(n);

    std::memset(hmax, -1, sizeof(hmax));
    std::memset(lmax, -1, sizeof(lmax));

    for (int i = 0, x, y; i < n; ++i)
    {
        read(x), read(y);

        int xh = x >> 9, xl = x & 511, yh = y >> 9, yl = y & 511;
        for (int th = 0; th < 256; ++th)
        {
            chkmax(hmax[0][th][511 - xl], (th + xh) ^ yh);
            chkmax(hmax[1][th][512 - xl], (th + xh + 1) ^ yh);
        }

        for (int tl = 0; tl < 512; ++tl)
            if (tl + xl < 512)
                chkmax(lmax[0][xh][yh][tl], (tl + xl) ^ yl);
            else
                chkmax(lmax[1][xh][yh][tl], (tl + xl - 512) ^ yl);
    }

    for (int th = 0; th < 256; ++th)
    {
        for (int tl = 511; tl >= 0; --tl)
            chkmax(hmax[0][th][tl], hmax[0][th][tl + 1]);
        for (int tl = 1; tl <= 512; ++tl)
            chkmax(hmax[1][th][tl], hmax[1][th][tl - 1]);
    }

    int q;
    read(q);
    for (int i = 0, t; i < q; ++i)
    {
        read(t);

        int th = t >> 9, tl = t & 511, res = 0;
        for (int pro = 0; pro < 2; ++pro)
        {
            int rh = hmax[pro][th][tl];

            if (rh != -1)
            {
                for (int xh = 0; xh < 256; ++xh)
                {
                    int yh = rh ^ (xh + th + pro);

                    if (yh < 256)
                    {
                        int rl = lmax[pro][xh][yh][tl];

                        if (rl != -1)
                            chkmax(res, rh << 9 | rl);
                    }
                }
            }
        }

        std::cout << res << '\n';
    }
    return 0;
}