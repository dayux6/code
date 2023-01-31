#include <bits/stdc++.h>

int main()
{
    int l1, r1, l2, r2;
    std::cin >> l1 >> r1 >> l2 >> r2;
    int *cnt = new int[std::max(r1, r2) + 1]();
    for (int i = l1; i <= r1; ++i)
        ++cnt[i];
    for (int i = l2; i <= r2; ++i)
        ++cnt[i];
    int ans = 0;
    for (int i = 0; i <= std::max(r1, r2); ++i)
        if (cnt[i] == 2)
            ++ans;
    std::cout << std::max(0, ans - 1) << std::endl;
    return 0;
}