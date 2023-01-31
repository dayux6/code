#include <bits/stdc++.h>

int main()
{
    freopen("A.in", "r", stdin);
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;
    bool *flg = new bool[std::max(b, d) + 2]();
    for (int i = a; i <= b; ++i)
        flg[i] = true;
    for (int i = c; i <= d; ++i)
        flg[i] = true;
    int cnt = 0;
    for (int i = 0; i <= std::max(b, d) + 1; ++i)
        if (flg[i])
            ++cnt;
        else if (i > 0 && flg[i - 1])
            --cnt;
    std::cout << cnt << std::endl;
    return 0;
}