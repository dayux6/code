#include <bits/stdc++.h>

std::vector<long long> l({3});

char func(int n, int p)
{
    if (n == 0)
        return p ^ 1 ? 'o' : 'm';
    if (p <= l.at(n - 1))
        return func(n - 1, p);
    if (p + l.at(n - 1) > l.at(n))
        return func(n - 1, p + l.at(n - 1) - l.at(n));
    return p ^ (l.at(n - 1) + 1) ? 'o' : 'm';
}

int main()
{
    freopen("B.in", "r", stdin);
    int n;
    std::cin >> n;
    while (l.back() < n)
        l.emplace_back(l.back() * 2 + l.size() + 3);
    std::cout << func(l.size() - 1, n) << '\n';
    return 0;
}