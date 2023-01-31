#include <bits/stdc++.h>

const int n = 15;

int main()
{
    int r, c;
    std::cin >> r >> c;

    bool flg = false;
    if (r & 1 || c & 1)
    {
        if (r & 1)
            flg = std::min(r, n - r) <= c && c <= std::max(r, n - r);

        if (c & 1)
            flg |= std::min(c, n - c) <= r && r <= std::max(c, n - c);
    }

    std::cout << (flg ? "black" : "white") << std::endl;
    return 0;
}