#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("CF1702C.in");
#endif
using std::cout;

struct query
{
    int no, a, b;

    query(int _no, int _a, int _b) : no(_no), a(_a), b(_b) {}
};

int main()
{
    int t;
    cin >> t;
    for (int _ = 0; _ < t; ++_)
    {
        int n, k;
        cin >> n >> k;
        int *u = new int[n];
        std::vector<int> vct;
        for (int i = 0; i < n; ++i)
        {
            cin >> u[i];
            vct.emplace_back(u[i]);
        }
        std::sort(vct.begin(), vct.end());
        vct.erase(std::unique(vct.begin(), vct.end()), vct.end());
        int *p = new int[vct.size()];
        std::fill_n(p, vct.size(), -1);
        for (int i = 0; i < n; ++i)
        {
            u[i] = std::lower_bound(vct.begin(), vct.end(), u[i]) - vct.begin();
            if (p[u[i]] == -1)
                p[u[i]] = i;
        }
        bool *ans = new bool[k]();
        std::vector<query> q;
        for (int i = 0; i < k; ++i)
        {
            int a, b;
            cin >> a >> b;
            if (std::binary_search(vct.begin(), vct.end(), a) && std::binary_search(vct.begin(), vct.end(), b))
                q.emplace_back(i, (int)(std::lower_bound(vct.begin(), vct.end(), a) - vct.begin()), (int)(std::lower_bound(vct.begin(), vct.end(), b) - vct.begin()));
        }
        std::sort(q.begin(), q.end(), [=](query lhs, query rhs)
                  { return p[lhs.a] > p[rhs.a]; });
        int ptr = n;
        std::unordered_set<int> s;
        for (auto it = q.begin(); it != q.end(); ++it)
        {
            while (ptr > p[it->a])
                s.emplace(u[--ptr]);
            ans[it->no] = s.count(it->b);
        }
        for (int i = 0; i < k; ++i)
            cout << (ans[i] ? "YES\n" : "NO\n");
    }
    return 0;
}