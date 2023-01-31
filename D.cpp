#include <bits/stdc++.h>

struct cow
{
    int g, d;

    cow() { std::cin >> g >> d; }

    bool operator<(cow rhs) const { return d < rhs.d; }
};

int main()
{
    freopen("D.in", "r", stdin);
    int n;
    std::cin >> n;
    cow *c = new cow[n]();
    std::sort(c, c + n);
    int *f = new int[n]();
    for (int i = 1; i <= c[n - 1].d; ++i)
    {
        int max = 0;
        for (int j = 0; j < n; ++j)
        {
            int tmp = max + c[j].g;
            max = std::max(max, f[j]);
            if (i <= c[j].d)
                f[j] = tmp;
        }
    }
    int max = 0;
    for (int i = 0; i < n; ++i)
        max = std::max(max, f[i]);
    std::cout << max << std::endl;
    return 0;
}