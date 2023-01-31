#include <bits/stdc++.h>

const int maxn = 2e5;

int t[maxn + 1], v[maxn + 1];

struct CTS
{
private:
    long long sum;
    std::priority_queue<int> g;
    std::priority_queue<int, std::vector<int>, std::greater<int>> l;

public:
    CTS() { sum = 0; }

    int getsiz() { return g.size(); }

    int gettot() { return g.size() + l.size(); }

    void ins(int x)
    {
        if (!g.empty() && x < g.top())
        {
            l.push(g.top());
            sum -= g.top();
            g.pop();
            sum += x;
            g.push(x);
        }
        else
            l.push(x);
    }

    void inc()
    {
        sum += l.top();
        g.push(l.top());
        l.pop();
    }

    void dec()
    {
        sum -= g.top();
        l.push(g.top());
        g.pop();
    }

    long long getsum() { return sum; }
};

int main()
{
    std::freopen("CF799E.in", "r", stdin);

    int n, m, k;
    std::cin >> n >> m >> k;

    for (int i = 1; i <= n; ++i)
        std::cin >> t[i];

    int a;
    std::cin >> a;
    for (int i = 1; i <= a; ++i)
    {
        int x;
        std::cin >> x;
        v[x] += 1;
    }

    std::cin >> a;
    for (int i = 1; i <= a; ++i)
    {
        int x;
        std::cin >> x;
        v[x] += 2;
    }

    std::vector<std::pair<int, int>> book[4];
    for (int i = 1; i <= n; ++i)
        book[v[i]].emplace_back(t[i], i);

    for (int i = 1; i < 4; ++i)
        std::sort(book[i].begin(), book[i].end());

    int pos = -1, p1 = std::min(k, (int)book[1].size()) - 1, p2 = std::min(k, (int)book[2].size()) - 1;
    long long min = LLONG_MAX, sum = 0;
    CTS h;

    for (std::pair<int, int> pr : book[0])
        h.ins(pr.first);
    for (int i = 0; i < k && i < book[1].size(); ++i)
        sum += book[1].at(i).first;
    for (int i = k; i < book[1].size(); ++i)
        h.ins(book[1].at(i).first);
    for (int i = 0; i < k && i < book[2].size(); ++i)
        sum += book[2].at(i).first;
    for (int i = k; i < book[2].size(); ++i)
        h.ins(book[2].at(i).first);

    if (book[1].size() >= k && book[2].size() >= k && m - k * 2 >= 0 && h.gettot() >= m - k * 2)
    {
        pos = 0;
        while (h.getsiz() < m - k * 2)
            h.inc();
        min = std::min(min, sum + h.getsum());
        pos = 0;
    }

    for (int i = 1; i <= book[3].size() && i <= m; ++i)
    {
        if (p1 >= 0 && p1 >= k - i)
        {
            sum -= book[1].at(p1).first;
            h.ins(book[1].at(p1).first);
            --p1;
        }
        if (p2 >= 0 && p2 >= k - i)
        {
            sum -= book[2].at(p2).first;
            h.ins(book[2].at(p2).first);
            --p2;
        }

        sum += book[3].at(i - 1).first;

        if (p1 + 1 >= k - i && p2 + 1 >= k - i && i + p1 + 1 + p2 + 1 <= m && i + p1 + 1 + p2 + 1 + h.gettot() >= m)
        {
            while (i + p1 + 1 + p2 + 1 + h.getsiz() < m)
                h.inc();
            while (i + p1 + 1 + p2 + 1 + h.getsiz() > m)
                h.dec();

            if (sum + h.getsum() < min)
            {
                min = sum + h.getsum();
                pos = i;
            }
        }
    }

    if (pos == -1)
        std::cout << -1 << std::endl;
    else
        std::cout << min << std::endl;
    return 0;
}