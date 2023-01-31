#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, c, fa[1000006], h[1000006], l[1000006], sz[1000006], r[1000006], add, ans, sum[1000006];
struct tpl
{
    int first;
    int second;
    int third;
};
queue<tpl> q;
int find(int x)
{
    if (fa[x] == x)
        return x;
    return fa[x] = find(fa[x]);
}
void merge(int x, int y)
{
    r[find(x)] = max(r[find(x)], r[find(y)]);
    l[find(x)] = min(l[find(x)], l[find(y)]);
    sz[find(x)] += sz[find(y)];
    sum[find(x)] += sum[find(y)];
    fa[find(y)] = find(x);
    return;
}
int getmin(int x)
{
    if (find(l[find(x)]) == 0)
        return h[find(r[find(x)])];
    if (find(r[find(x)]) == n + 1)
        return h[find(l[find(x)])];
    return min(h[find(r[find(x)])], h[find(l[find(x)])]);
}
int getbound(int x)
{
    if (find(l[find(x)]) == 0)
        return 1;
    if (find(r[find(x)]) == n + 1)
        return 1;
    return 2;
}
signed main()
{
    freopen("brick.in", "r", stdin);
    // freopen("brick.out", "w", stdout);
    cin >> n >> c;
    fa[0] = 0;
    fa[n + 1] = n + 1;
    h[0] = h[n + 1] = 1e9;
    for (int i = 1; i <= n; i++)
        scanf("%lld", &h[i]), fa[i] = i, sz[i] = 1, sum[i] = 1, l[i] = i - 1, r[i] = i + 1;
    for (int i = 1; i < n; i++)
    {
        ans += c * abs(h[i] - h[i + 1]);
        if (h[i] == h[i + 1])
            merge(find(i), find(i + 1));
    }
    for (int i = 1; i <= n; i++)
    {
        if (find(i) == i && h[find(l[i])] > h[i] && h[find(r[i])] > h[i])
            q.push((tpl){i, sum[i], sz[i]});
    }
    //	cout<<ans<<endl;
    while (!q.empty())
    {
        tpl p = q.front();
        q.pop(); // if(find(p.first)!=p.first)return 0;
        int dif = getmin(p.first) - h[p.first], w = getbound(p.first);
        if (p.second + p.third * 2 * (dif - 1) <= c * w)
        {
            h[p.first] += dif;
            ans -= c * w * dif - (p.second * 2 + p.third * 2 * (dif - 1)) * dif / 2;
            sum[p.first] += p.third * 2 * dif;
            if (h[find(l[p.first])] == h[p.first])
                merge(p.first, find(l[p.first]));
            if (h[find(r[p.first])] == h[p.first])
                merge(p.first, find(r[p.first]));
            if (find(p.first) == p.first && h[find(l[p.first])] > h[p.first] &&
                h[find(r[p.first])] > h[p.first] && sz[p.first] != n)
                q.push((tpl){p.first, sum[p.first], sz[p.first]});
        }
        else
        {
            add = (c * w - p.second) / (p.third * 2);
            if (p.second <= c * w)
            { // if(add>dif)return 0;
                h[p.first] += add + 1;
                ans -= c * w * (add + 1) - (p.second * 2 + p.third * 2 * add) * (add + 1) / 2;
            }
        }
        //		cout<<ans<<" "<<p.first<<endl;
    }

    for (int i = 1; i <= n; ++i)
        cout << h[find(i)] << ' ';
    std::cout << std::endl;

    cout << ans << endl;
    return 0;
}