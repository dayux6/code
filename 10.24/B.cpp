#include <bits/stdc++.h>

const int maxn = 3e6;

int ans;
char str[maxn + 1];

struct trie
{
    struct node
    {
        int cnt;
        std::unordered_map<char, node *> s;

        node() : cnt(0) {}
    } * rt;
    trie() : rt(new node()) {}

    void insert(char *s)
    {
        int len = std::strlen(s + 1);
        node *cur = rt;
        for (int i = len; i >= 1; --i)
        {
            if (cur->s.count(s[i]) == 0)
                cur->s.emplace(s[i], new node());
            cur = cur->s.at(s[i]);
        }
        ++cur->cnt;
    }
};

int dfs(trie::node *cur)
{
    int max = 0, sec = 0, cnt = 0;
    for (std::pair<char, trie::node *> pr : cur->s)
    {
        cnt += pr.second->cnt != 0;

        int tmp = dfs(pr.second);
        if (tmp > sec)
            sec = tmp;
        if (sec > max)
            std::swap(max, sec);
    }

    ans = std::max(ans, max + sec + cur->cnt + std::max(0, cnt - 2));
    if (cur->cnt != 0)
        return max + cur->cnt + std::max(0, cnt - 1);
    else
        return 0;
}

int main()
{
    std::freopen("string.in", "r", stdin);
    std::freopen("string.out", "w", stdout);

    int n;
    std::cin >> n;

    trie t;
    for (int i = 0; i < n; ++i)
    {
        std::scanf("%s", str + 1);
        t.insert(str);
    }

    dfs(t.rt);

    std::cout << ans << std::endl;
    return 0;
}