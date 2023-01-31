#include <bits/stdc++.h>

int main()
{
    freopen("C.in", "w", stdout);
    srand(time(0));
    int n = 15;
    std::cout << n << std::endl;
    int *a = new int[n + 1];
    std::iota(a + 1, a + n + 1, 1);
    std::random_shuffle(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i)
        std::cout << i << ' ' << a[i] << std::endl;
    return 0;
}