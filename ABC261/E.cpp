#include <bits/stdc++.h>

int main()
{
    freopen("E.in", "r", stdin);
    int n, c;
    std::cin >> n >> c;
    bool *a[2][32];
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 32; ++j)
        {
            a[i][j] = new bool[n + 1];
            a[i][j][0] = i;
        }
    for (int i = 1; i <= n; ++i)
    {
        int t, x;
        std::cin >> t >> x;
        for (int k = 0; k < 32; ++k)
        {
            bool b = (x >> k) & 1;
            switch (t)
            {
            case 1:
            {
                a[0][k][i] = a[0][k][i - 1] & b;
                a[1][k][i] = a[1][k][i - 1] & b;
                break;
            }
            case 2:
            {
                a[0][k][i] = a[0][k][i - 1] | b;
                a[1][k][i] = a[1][k][i - 1] | b;
                break;
            }
            case 3:
            {
                a[0][k][i] = a[0][k][i - 1] ^ b;
                a[1][k][i] = a[1][k][i - 1] ^ b;
                break;
            }
            }
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        int nxt = 0;
        for (int j = 0; j < 32; ++j)
            if (a[(c >> j) & 1][j][i])
                nxt += 1 << j;
        std::cout << nxt << std::endl;
        c = nxt;
    }
    return 0;
}