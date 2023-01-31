#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("CF1702E.in");
#endif
using std::cout;

class UnionFind
{
private:
    int n, *fa;

public:
    UnionFind(int);
    int find(int);
    void merge(int, int);
};

UnionFind::UnionFind(int _n) : n(_n), fa(new int[_n + 1]) { std::iota(fa + 1, fa + n + 1, 1); }

int UnionFind::find(int x)
{
    while (x != fa[x])
        x = fa[x] = fa[fa[x]];
    return x;
}

void UnionFind::merge(int x, int y) { fa[find(x)] = find(y); }

int main()
{
    int t;
    cin >> t;
    for (int _ = 0; _ < t; ++_)
    {
        int n;
        cin >> n;
        int *pre = new int[n + 1](), *cnt = new int[n + 1]();
        bool flg = true;
        UnionFind uf(n * 2);
        for (int i = 1; i <= n; ++i)
        {
            int a, b;
            cin >> a >> b;
            ++cnt[a];
            ++cnt[b];
            if (a == b || cnt[a] > 2 || cnt[b] > 2)
                flg = false;
            if (pre[a] == 0)
                pre[a] = i;
            else
            {
                uf.merge(i + n, pre[a]);
                uf.merge(i, pre[a] + n);
            }
            if (pre[b] == 0)
                pre[b] = i;
            else
            {
                uf.merge(i + n, pre[b]);
                uf.merge(i, pre[b] + n);
            }
        }
        for (int i = 1; i <= n; ++i)
            if (uf.find(i) == uf.find(i + n))
            {
                flg = false;
                break;
            }
        cout << (flg ? "YES\n" : "NO\n");
    }
    return 0;
}