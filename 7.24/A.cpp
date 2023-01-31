#include <bits/stdc++.h>

int main()
{
    freopen("A.in", "r", stdin);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    int a, cnt = 0, ans;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> a;
        if (cnt == 0)
            ans = a;
        if (a == ans)
            ++cnt;
        else
            --cnt;
    }
    std::cout << ans << std::endl;
    return 0;
}