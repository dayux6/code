#include <bits/stdc++.h>

class BST
{
private:
    struct node
    {
        int v;
        node *ls, *rs;

        node(int _v) : v(_v), ls(nullptr), rs(nullptr) {}
    } * rt;
    void insert(node *&, int);
    void dfs(node *);

public:
    BST();
    void insert(int);
    void dfs();
};

BST::BST() : rt(nullptr) {}

void BST::insert(node *&x, int v)
{
    if (x == nullptr)
        x = new node(v);
    else if (v < x->v)
        insert(x->ls, v);
    else
        insert(x->rs, v);
}

void BST::dfs(node *x)
{
    if (x == nullptr)
        return;
    std::cout << x->v << ' ';
    dfs(x->ls);
    dfs(x->rs);
}

void BST::insert(int v) { insert(rt, v); }

void BST::dfs() { dfs(rt); }

int main()
{
    freopen("B.in", "r", stdin);
    int n;
    std::cin >> n;
    BST t;
    for (int i = 0; i < n; ++i)
    {
        int a;
        std::cin >> a;
        t.insert(a);
    }
    t.dfs();
    return 0;
}