#include <bits/stdc++.h>

int main()
{
    int n;
    std::cin >> n;

    int l = 1, r = n;
    while (l < r)
    {
        int mid = (l + r) / 2;
        std::cout << "? " << l << ' ' << mid << ' ' << 1 << ' ' << n << std::endl;
        int tmp;
        std::cin >> tmp;
        if (tmp == mid - l + 1)
            l = mid + 1;
        else
            r = mid;
    }

    int x = l;
    l = 1;
    r = n;
    while (l < r)
    {
        int mid = (l + r) / 2;
        std::cout << "? " << 1 << ' ' << n << ' ' << l << ' ' << mid << std::endl;
        int tmp;
        std::cin >> tmp;
        if (tmp == mid - l + 1)
            l = mid + 1;
        else
            r = mid;
    }
    int y = r;

    std::cout << "! " << x << ' ' << y << std::endl;
    return 0;
}