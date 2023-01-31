#include <bits/stdc++.h>

int main()
{
    freopen("A.in", "r", stdin);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    int *a = new int[n + 1], *l = new int[n + 1]();
    std::vector<int> vct;
    std::stack<int> s;
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> a[i];
        vct.emplace_back(a[i]);
        while (!s.empty() && a[i] >= a[s.top()])
            s.pop();
        if (!s.empty())
            l[i] = s.top();
        s.emplace(i);
    }
    std::sort(vct.begin(), vct.end());
    vct.erase(std::unique(vct.begin(), vct.end()), vct.end());
    long long *cnt = new long long[vct.size()]();
    while (!s.empty())
        s.pop();
    for (int i = n; i >= 1; --i)
    {
        a[i] = std::lower_bound(vct.begin(), vct.end(), a[i]) - vct.begin();
        while (!s.empty() && a[i] > a[s.top()])
            s.pop();
        if (s.empty())
            cnt[a[i]] += 1ll * (i - l[i]) * (n - i + 1);
        else
            cnt[a[i]] += 1ll * (i - l[i]) * (s.top() - i);
        s.emplace(i);
    }
    long long *pre = new long long[vct.size()], *suf = new long long[vct.size()];
    pre[0] = cnt[0];
    for (int i = 1; i < vct.size(); ++i)
        pre[i] = pre[i - 1] + cnt[i];
    suf[vct.size() - 1] = cnt[vct.size() - 1];
    for (int i = vct.size() - 2; i >= 0; --i)
        suf[i] = suf[i + 1] + cnt[i];
    for (int i = 0; i < q; ++i)
    {
        char op;
        int k;
        std::cin >> op >> k;
        switch (op)
        {
        case '>':
            if (k >= vct.back())
                std::cout << "0\n";
            else
                std::cout << suf[std::upper_bound(vct.begin(), vct.end(), k) - vct.begin()] << '\n';
            break;
        case '=':
        {
            if (std::binary_search(vct.begin(), vct.end(), k))
                std::cout << cnt[std::lower_bound(vct.begin(), vct.end(), k) - vct.begin()] << '\n';
            else
                std::cout << "0\n";
            break;
        }
        case '<':
            if (k <= vct.front())
                std::cout << "0\n";
            else
                std::cout << pre[--std::lower_bound(vct.begin(), vct.end(), k) - vct.begin()] << '\n';
            break;
        }
    }
    return 0;
}