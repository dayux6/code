#include <bits/stdc++.h>

int *a, *max, *min;

int divide(int l, int r)
{
    if (l == r)
        return 1;
    int mid = (l + r) / 2, ret = divide(l, mid) + divide(mid + 1, r);
    max[mid] = min[mid] = a[mid];
    for (int i = mid - 1; i >= l; --i)
    {
        max[i] = std::max(max[i + 1], a[i]);
        min[i] = std::min(min[i + 1], a[i]);
    }
    max[mid + 1] = min[mid + 1] = a[mid + 1];
    for (int i = mid + 2; i <= r; ++i)
    {
        max[i] = std::max(max[i - 1], a[i]);
        min[i] = std::min(min[i - 1], a[i]);
    }
    for (int i = l; i <= mid; ++i)
    {
        int len = max[i] - min[i] + 1;
        if (i + len - 1 <= r && i + len - 1 > mid && max[i] > max[i + len - 1] && min[i] < min[i + len - 1])
            ++ret;
    }
    for (int i = mid + 1; i <= r; ++i)
    {
        int len = max[i] - min[i] + 1;
        if (i - len + 1 >= l && i - len + 1 <= mid && max[i] > max[i - len + 1] && min[i] < min[i - len + 1])
            ++ret;
    }
    std::unordered_map<int, int> cnt;
    int pmin = mid, pmax = mid + 1;
    for (int i = mid; i >= l; --i)
    {
        while (pmin < r && min[pmin + 1] > min[i])
        {
            ++pmin;
            ++cnt[max[pmin] - pmin];
        }
        while (pmax <= pmin && max[pmax] <= max[i])
        {
            --cnt[max[pmax] - pmax];
            ++pmax;
        }
        ret += cnt[min[i] - i];
    }
    cnt.clear();
    pmin = mid + 1;
    pmax = mid;
    for (int i = mid; i >= l; --i)
    {
        while (pmax < r && max[pmax + 1] < max[i])
        {
            ++pmax;
            ++cnt[min[pmax] + pmax];
        }
        while (pmin <= pmax && min[pmin] >= min[i])
        {
            --cnt[min[pmin] + pmin];
            ++pmin;
        }
        ret += cnt[max[i] + i];
    }
    return ret;
}

int main()
{
    freopen("C.in", "r", stdin);
    int n;
    std::cin >> n;
    a = new int[n + 1];
    for (int i = 1; i <= n; ++i)
    {
        int x, y;
        std::cin >> x >> y;
        a[x] = y;
    }
    max = new int[n + 1];
    min = new int[n + 1];
    std::cout << divide(1, n) << std::endl;
    return 0;
}