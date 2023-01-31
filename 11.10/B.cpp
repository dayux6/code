#include <bits/stdc++.h>

const int maxn = 1e5, maxlg = 30;

int a[maxn + 1], xs[maxn + 1], pre[maxn + 1], suf[maxn + 1];

namespace trie
{
    int tot, rt[maxn + 1];

    struct node
    {
        int siz, s[2];

        node() { siz = s[0] = s[1] = 0; }
    } t[(maxlg + 2) * (maxn + 1) + 1];

    void insert(int x, int &r, int pre)
    {
        ++tot;
        r = tot;
        int cur = tot;
        for (int i = maxlg; i >= 0; --i)
        {
            bool k = (x >> i) & 1;

            t[cur].siz = t[pre].siz + 1;
            t[cur].s[k ^ 1] = t[pre].s[k ^ 1];
            ++tot;
            t[cur].s[k] = tot;

            pre = t[pre].s[k];
            cur = t[cur].s[k];
        }

        t[cur].siz = t[pre].siz + 1;
    }

    int query(int x, int y, int w, int lim)
    {
        int ret = 0;
        for (int i = 30; i >= 0; --i)
        {
            bool kw = (w >> i) & 1, kl = (lim >> i) & 1;

            if (kl)
            {
                x = t[x].s[kw ^ 1];
                y = t[y].s[kw ^ 1];
            }
            else
            {
                ret += t[t[y].s[kw ^ 1]].siz - t[t[x].s[kw ^ 1]].siz;
                x = t[x].s[kw];
                y = t[y].s[kw];
            }
        }

        return ret;
    }
};

int main()
{
    std::freopen("xor.in", "r", stdin);
    std::freopen("xor.out", "w", stdout);

    int n;
    std::cin >> n;

    trie::tot = 0;
    trie::insert(0, trie::rt[0], 0);
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> a[i];
        xs[i] = xs[i - 1] ^ a[i];
        trie::insert(xs[i], trie::rt[i], trie::rt[i - 1]);
    }

    std::stack<int> s;
    for (int i = 1; i <= n; ++i)
    {
        while (!s.empty() && a[s.top()] <= a[i])
            s.pop();
        pre[i] = s.empty() ? 0 : s.top();
        s.emplace(i);
    }

    while (!s.empty())
        s.pop();
    for (int i = n; i >= 1; --i)
    {
        while (!s.empty() && a[s.top()] < a[i])
            s.pop();
        suf[i] = s.empty() ? n + 1 : s.top();
        s.emplace(i);
    }

    long long cnt = 1ll * (n + 1) * n / 2;
    for (int i = 1; i <= n; ++i)
        if (i - pre[i] < suf[i] - i)
            for (int j = pre[i] + 1; j <= i; ++j)
                cnt -= trie::query(trie::rt[i - 1], trie::rt[suf[i] - 1], xs[j - 1], a[i]);
        else
            for (int j = i; j < suf[i]; ++j)
                cnt -= trie::query(pre[i] == 0 ? 0 : trie::rt[pre[i] - 1], trie::rt[i - 1], xs[j], a[i]);
    std::cout << cnt << std::endl;
    return 0;
}