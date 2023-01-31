#include <bits/stdc++.h>
#include <bits/extc++.h>

const int maxn = 1e5;

int a[maxn + 1];
bool vis[maxn + 1];

int main()
{
    freopen("D.in", "r", stdin);
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];

    std::sort(a + 1, a + n + 1);

    int mid = (n + 1) / 2, p = -1;

    if (a[mid] == a[mid + 1])
    {
        while (mid < n && a[mid] == a[mid + 1])
            ++mid;
        std::cout << a[mid - 1] << ' ' << a[mid] << ' ';
        int l = mid - 2, r = n;
        while (l >= 1 || r > mid)
        {
            if (r > mid)
            {
                std::cout << a[r] << ' ';
                --r;
            }
            if (l >= 1)
            {
                std::cout << a[l] << ' ';
                --l;
            }
        }
        std::cout << std::endl;
        return 0;
    }

    for (int i = mid; i >= 1; --i)
        if (a[i] == a[i + 1])
        {
            p = i;
            break;
        }

    __gnu_pbds::tree<long long, __gnu_pbds::null_type, std::less<long long>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> t;
    if (~p)
    {
        while (p < n && a[p] == a[p + 1])
            ++p;
        std::cout << a[p - 1] << ' ' << a[p] << ' ';
        vis[p - 1] = vis[p] = true;
        t.insert(1ll * a[p - 1] * (n + 1) + p - 1);
        t.insert(1ll * a[p] * (n + 1) + p);
        int l = p - 2, r = n;
        while (l >= 1 && r > p)
        {
            std::cout << a[r] << ' ' << a[l] << ' ';
            vis[l] = vis[r] = true;
            t.insert(1ll * a[l] * (n + 1) + l);
            t.insert(1ll * a[r] * (n + 1) + r);
            --l;
            --r;
        }
    }
    else
    {
        std::cout << a[1] << ' ';
        vis[1] = true;
        t.insert(a[1] * (n + 1) + 1);
    }

    std::set<long long> s;
    for (int i = 1; i <= n; ++i)
        if (!vis[i])
            s.insert(1ll * a[i] * (n + 1) + i);
    while (!s.empty())
        if (t.size() & 1)
        {
            int med = *t.find_by_order((t.size() - 1) / 2) / (n + 1), tmp = t.size() ^ 1 ? *t.find_by_order((t.size() + 1) / 2) / (n + 1) : INT_MAX / 2;
            if (*s.begin() / (n + 1) * 2 < med + tmp)
            {
                auto it = --s.lower_bound((*s.begin() / (n + 1) * 2 - med + 1) * (n + 1));
                std::cout << *it / (n + 1) << ' ';
                t.insert(*it);
                s.erase(it);
            }
            else
            {
                std::cout << *s.rbegin() / (n + 1) << ' ';
                t.insert(*s.rbegin());
                s.erase(--s.end());
            }
        }
        else
        {
            int med = *t.find_by_order(t.size() / 2) / (n + 1);
            if (*s.begin() / (n + 1) < med)
            {
                std::cout << *s.begin() / (n + 1) << ' ';
                t.insert(*s.begin());
                s.erase(s.begin());
            }
            else
            {
                std::cout << *s.rbegin() / (n + 1) << ' ';
                t.insert(*s.rbegin());
                s.erase(--s.end());
            }
        }
    std::cout << std::endl;
    return 0;
}