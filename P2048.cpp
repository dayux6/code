#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("P2048.in");
#endif
using std::cout;

struct node
{
    int h, l, r, p, v;

    node(int _h, int _l, int _r, int _p, int _v) : h(_h), l(_l), r(_r), p(_p), v(_v) {}

    bool operator<(node rhs) const { return v < rhs.v; }
};

int main()
{
    int n, k, L, R;
    cin >> n >> k >> L >> R;
    int *s = new int[n + 1];
    s[0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        cin >> s[i];
        s[i] += s[i - 1];
    }
    int lg = log2(n), **st = new int *[n + 1];
    for (int i = 1; i <= n; ++i)
    {
        st[i] = new int[lg + 1];
        st[i][0] = i;
    }
    for (int i = 1; i <= lg; ++i)
        for (int j = 1; j + (1 << i) - 1 <= n; ++j)
            if (s[st[j][i - 1]] > s[st[j + (1 << (i - 1))][i - 1]])
                st[j][i] = st[j][i - 1];
            else
                st[j][i] = st[j + (1 << (i - 1))][i - 1];
    auto query = [=](int l, int r)
    {
        int k = log2(r - l + 1);
        if (s[st[l][k]] > s[st[r - (1 << k) + 1][k]])
            return st[l][k];
        else
            return st[r - (1 << k) + 1][k];
    };
    std::priority_queue<node> q;
    for (int i = 1; i + L - 1 <= n; ++i)
    {
        int p = query(i + L - 1, std::min(i + R - 1, n));
        q.emplace(i, i + L - 1, std::min(i + R - 1, n), p, s[p] - s[i - 1]);
    }
    long long sum = 0;
    for (int i = 0; i < k; ++i)
    {
        node x = q.top();
        q.pop();
        sum += x.v;
        if (x.p != x.l)
        {
            int p = query(x.l, x.p - 1);
            q.emplace(x.h, x.l, x.p - 1, p, s[p] - s[x.h - 1]);
        }
        if (x.p != x.r)
        {
            int p = query(x.p + 1, x.r);
            q.emplace(x.h, x.p + 1, x.r, p, s[p] - s[x.h - 1]);
        }
    }
    cout << sum << std::endl;
    return 0;
}