#include <bits/stdc++.h>

int main()
{
    freopen("F.in", "r", stdin);
    int n, x, y, z;
    std::cin >> n >> x >> y >> z;
    long long sum = 0;
    std::priority_queue<int> q[2];
    for (int i = 0; i < n; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        while (a < b)
        {
            int w;
            if (!q[1].empty() && i * z - q[1].top() < x)
            {
                w = i * z - q[1].top();
                q[1].pop();
            }
            else
                w = x;
            sum += w;
            q[0].emplace(i * z + w);
            ++a;
        }
        while (a > b)
        {
            int w;
            if (!q[0].empty() && i * z - q[0].top() < y)
            {
                w = i * z - q[0].top();
                q[0].pop();
            }
            else
                w = y;
            sum += w;
            q[1].emplace(i * z + w);
            --a;
        }
    }
    std::cout << sum << std::endl;
    return 0;
}