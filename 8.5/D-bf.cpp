#include <bits/stdc++.h>
#include <bits/extc++.h>

const int maxn = 1e5;

int a[maxn + 1];

int main()
{
    freopen("D.in", "r", stdin);
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];

    std::sort(a + 1, a + n + 1, std::greater<int>());

    bool b = true;
    __gnu_pbds::tree<int, __gnu_pbds::null_type, std::less<int>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> t;
    do
    {
        int pre = a[1] * 2;
        bool flg = true;
        t.insert(a[1] * (n + 1) + 1);
        for (int i = 2; i <= n; ++i)
        {
            t.insert(a[i] * (n + 1) + i);
            int med;
            if (i & 1)
                med = *t.find_by_order((i - 1) / 2) / (n + 1) * 2;
            else
                med = *t.find_by_order(i / 2 - 1) / (n + 1) + *t.find_by_order(i / 2) / (n + 1);
            if (med < pre)
            {
                flg = false;
                break;
            }
            pre = med;
        }
        if (flg)
        {
            b = false;
            for (int i = 1; i <= n; ++i)
                std::cout << a[i] << ' ';
            std::cout << std::endl;
            break;
        }
        t.clear();
    } while (std::prev_permutation(a + 1, a + n + 1));
    if (b)
        std::cout << "QwQ" << std::endl;
    return 0;
}