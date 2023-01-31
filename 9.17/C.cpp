#include <bits/stdc++.h>

const int maxn = 2e5, maxlg = 17;

int l[maxn], r[maxn], max[maxn + 1][2], st[maxn + 1][maxlg + 1][2];

int main()
{
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
    int n, m;
    std::cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        max[i][0] = max[i][1] = i;
    for (int i = 0; i < m; ++i)
    {
        std::cin >> l[i] >> r[i];

        max[l[i]][1] = std::max(max[l[i]][1], r[i]);
        if (max[l[i]][0] < max[l[i]][1])
            std::swap(max[l[i]][0], max[l[i]][1]);
    }

    st[1][0][0] = max[1][0];
    st[1][0][1] = max[1][1];
    for (int i = 2; i <= n; ++i)
    {
        std::array<int, 4> tmp({max[i - 1][0], max[i - 1][1], max[i][0], max[i][1]});
        std::sort(tmp.begin(), tmp.end());
        max[i][0] = st[i][0][0] = tmp.at(3);
        max[i][1] = st[i][0][1] = tmp.at(2);
    }

    int lg = log2(n);
    for (int i = 1; i <= lg; ++i)
        for (int j = 1; j <= n; ++j)
        {
            st[j][i][0] = st[st[j][i - 1][0]][i - 1][0];
            st[j][i][1] = st[st[j][i - 1][0]][i - 1][1];
        }

    int q;
    std::cin >> q;
    for (int _ = 0; _ < q; ++_)
    {
        int id, s, t;
        std::cin >> id >> s >> t;
        --id;

        if (s >= t)
            std::cout << 0 << std::endl;
        else
        {
            int res = 0;
            if (t <= l[id] || s >= r[id])
            {
                for (int i = lg; i >= 0; --i)
                    if (st[s][i][0] < t)
                    {
                        s = st[s][i][0];
                        res |= 1 << i;
                    }
                s = st[s][0][0];
                ++res;
            }
            else
            {
                if (s < l[id])
                {
                    for (int i = lg; i >= 0; --i)
                        if (st[s][i][0] < l[id])
                        {
                            s = st[s][i][0];
                            res |= 1 << i;
                        }
                    s = st[s][0][0];
                    ++res;
                }

                if (s >= l[id] && s < t)
                {
                    if (t <= r[id])
                    {
                        for (int i = lg; i >= 0; --i)
                            if (st[s][i][1] < t)
                            {
                                s = st[s][i][1];
                                res += 1 << i;
                            }
                        s = st[s][0][1];
                        ++res;
                    }
                    else
                    {
                        if (max[s][0] == r[id])
                        {
                            for (int i = lg; i >= 0; --i)
                                if (max[st[s][i][1]][0] <= r[id])
                                {
                                    s = st[s][i][1];
                                    res += 1 << i;
                                }
                            s = st[s][0][1];
                            ++res;
                        }

                        if (s <= r[id])
                        {
                            s = max[s][0];
                            ++res;
                        }

                        if (s <= r[id])
                        {
                            std::cout << -1 << std::endl;
                            continue;
                        }

                        if (s < t)
                        {
                            for (int i = lg; i >= 0; --i)
                                if (st[s][i][0] < t)
                                {
                                    s = st[s][i][0];
                                    res += 1 << i;
                                }
                            s = st[s][0][0];
                            ++res;
                        }
                    }
                }
            }
            if (s < t)
                std::cout << -1 << std::endl;
            else
                std::cout << res << std::endl;
        }
    }
    return 0;
}