#include <bits/stdc++.h>

int main()
{
    freopen("A.in", "r", stdin);
    int n;
    std::cin >> n;
    int cnt = 0, max = 0;
    for (int i = 0; i < n; ++i)
    {
        bool b;
        std::cin >> b;
        if (b)
            cnt++;
        else if (cnt != 0)
        {
            max = std::max(max, cnt);
            cnt = 0;
        }
    }
    std::cout << max << '\n';
    return 0;
}