#include <bits/stdc++.h>

int cnt[7][7];

int main()
{
    freopen("C.in", "r", stdin);
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i)
    {
        char c;
        int v;
        std::cin >> c >> v;
        v = (v % 7 + 7) % 7;
        switch (c)
        {
        case 'B':
            ++cnt[0][v];
            break;
        case 'E':
            ++cnt[1][v];
            break;
        case 'S':
            ++cnt[2][v];
            break;
        case 'I':
            ++cnt[3][v];
            break;
        case 'G':
            ++cnt[4][v];
            break;
        case 'O':
            ++cnt[5][v];
            break;
        case 'M':
            ++cnt[6][v];
            break;
        }
    }
    long long ans = 0;
    for (int i0 = 0; i0 < 7; ++i0)
        if (cnt[0][i0] != 0)
            for (int i1 = 0; i1 < 7; ++i1)
                if (cnt[1][i1] != 0)
                    for (int i2 = 0; i2 < 7; ++i2)
                        if (cnt[2][i2] != 0)
                            for (int i3 = 0; i3 < 7; ++i3)
                                if (cnt[3][i3] != 0)
                                    for (int i4 = 0; i4 < 7; ++i4)
                                        if (cnt[4][i4] != 0)
                                            for (int i5 = 0; i5 < 7; ++i5)
                                                if (cnt[5][i5] != 0)
                                                    for (int i6 = 0; i6 < 7; ++i6)
                                                        if (cnt[6][i6] != 0 && ((i0 + i1 + i2 + i2 + i3 + i1) % 7 == 0 || (i4 + i5 + i1 + i2) % 7 == 0 || (i6 + i5 + i5) % 7 == 0))
                                                            ans += 1ll * cnt[0][i0] * cnt[1][i1] * cnt[2][i2] * cnt[3][i3] * cnt[4][i4] * cnt[5][i5] * cnt[6][i6];
    std::cout << ans << std::endl;
    return 0;
}