#include <bits/stdc++.h>

void read(int &x)
{
    x = 0;
    char c = getchar();

    while (!isdigit(c))
        c = getchar();

    while (isdigit(c))
    {
        x = x * 10 + (c ^ 48);
        c = getchar();
    }
}

const int maxn = 1e4;

int a[maxn];
std::bitset<maxn + 1> flg;
std::vector<int> prime;

void seive(int lim)
{
    for (int i = 2; i <= lim; ++i)
    {
        if (!flg.test(i))
            prime.push_back(i);

        for (int j = i * 2; j <= lim; j += i)
            flg.set(j);
    }
}

int main()
{
    freopen("num.in", "r", stdin);
    freopen("num.out", "w", stdout);

    int n;
    read(n);

    int sum = 0, max = 0;
    for (int i = 0; i < n; ++i)
    {
        read(a[i]);
        if (i > 0 && a[i] < a[i - 1])
        {
            sum += a[i - 1] - a[i];
            a[i] = a[i - 1];
        }
        max = std::max(max, a[i]);
    }

    seive(max);

    int min = INT_MAX;
    for (int v : prime)
    {
        int tmp = 0;
        for (int i = 0; i < n; ++i)
            tmp += v * std::ceil(1.0 * a[i] / v) - a[i];
        min = std::min(min, tmp);
    }

    std::cout << sum + min << std::endl;
    return 0;
}