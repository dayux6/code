#include <bits/stdc++.h>

const int maxn = 2e5;

int m[maxn + 1];
std::vector<int> s[maxn + 1];

std::priority_queue<int> dfs(int x)
{
    std::priority_queue<int> ret;
    for (int v : s[x])
    {
        std::priority_queue<int> q = dfs(v);

        if (ret.size() < q.size())
            std::swap(ret, q);
        std::vector<int> vct;
        for (int i = 0; !q.empty(); ++i)
        {
            vct.push_back(std::max(ret.top(), q.top()));
            ret.pop();
            q.pop();
        }
        for (int v : vct)
            ret.push(v);
    }
    ret.push(m[x]);
    return ret;
}

int main()
{
    freopen("D.in", "r", stdin);
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
        std::cin >> m[i];
    for (int i = 2; i <= n; ++i)
    {
        int fa;
        std::cin >> fa;
        s[fa].push_back(i);
    }

    std::priority_queue<int> q = dfs(1);
    long long sum = 0;
    while (!q.empty())
    {
        sum += q.top();
        q.pop();
    }
    std::cout << sum << std::endl;
    return 0;
}