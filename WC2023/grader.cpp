#include <bits/stdc++.h>
using namespace std;

const int N = 500005;
template <class T>
void read(T &x)
{
	int sgn = 1;
	char ch;
	x = 0;
	for (ch = getchar(); (ch < '0' || ch > '9') && ch != '-'; ch = getchar())
		;
	if (ch == '-')
		ch = getchar(), sgn = -1;
	for (; '0' <= ch && ch <= '9'; ch = getchar())
		x = x * 10 + ch - '0';
	x *= sgn;
}

namespace grader{
	int n, lim1, lim2, cnt1 = 0, cnt2 = 0, p[N], v[N], perm[N], inv[N];
	int sz[N], nxt[N], fa[N], ch[N][2], mx[N];
	bool is_root[N];
	vector<int> child[N];
	void dfs1(int u)
	{
		sz[u] = 1, nxt[u] = 0;
		for (auto i : child[u])
		{
			dfs1(i);
			if (!nxt[u] || sz[nxt[u]] < sz[i])
				nxt[u] = i;
			sz[u] += sz[i];
		}
	}

	void pushup(int u)
	{
		mx[u] = perm[u];
		if (ch[u][0])
			mx[u] = max(mx[u], mx[ch[u][0]]);
		if (ch[u][1])
			mx[u] = max(mx[u], mx[ch[u][1]]);
	}
	int vertex_list[N];
	int build_tree(int l, int r)
	{
		int s = sz[vertex_list[l]] - sz[nxt[vertex_list[r]]], sum = 0, pos = l;
		for (; pos <= r; pos++)
		{
			sum += sz[vertex_list[pos]] - sz[nxt[vertex_list[pos]]];
			if (sum > (s >> 1))
				break;
		}
		int u = vertex_list[pos];
		is_root[u] = false, ch[u][0] = ch[u][1] = 0;
		if (pos > l)
		{
			ch[u][0] = build_tree(l, pos - 1);
			fa[ch[u][0]] = u;
		}
		if (pos < r)
		{
			ch[u][1] = build_tree(pos + 1, r);
			fa[ch[u][1]] = u;
		}
		pushup(u);
		return u;
	}
	void dfs2(int u, int pre)
	{
		int tot = 0;
		vector<int> vec;
		for (int v = u; v; v = nxt[v])
			vec.push_back(v), vertex_list[++tot] = v;
		int rt = build_tree(1, tot);
		is_root[rt] = true, fa[rt] = pre;
		for (auto i : vec)
		{
			for (auto j : child[i])
			{
				if (j != nxt[i])
					dfs2(j, i);
			}
		}
	}
	void init()
	{
		read(n), read(lim1), read(lim2);
		for (int i = 2; i <= n; i++)
			read(p[i]), child[p[i]].push_back(i);
		for (int i = 2; i <= n; i++)
		{
			read(v[i]);
			perm[i] = v[i], inv[v[i]] = i;
		}
		sz[0] = perm[0] = perm[1] = 0;
		dfs1(1), dfs2(1, 0);
	}

	void change(int u, int x)
	{
		perm[u] = x;
		for (;; u = fa[u])
		{
			pushup(u);
			if (is_root[u])
				break;
		}
	}
	void exchange(int x, int y)
	{
		if (x == y || x <= 0 || x >= n || y <= 0 || y >= n)
		{
			fprintf(stderr, "Invalid call of exchange(%d, %d)!", x, y);
			exit(0);
		}
		if (++cnt1 > lim1)
		{
			fprintf(stderr, "Too many exchanges!\n");
			exit(0);
		}
		int u = inv[x], v = inv[y];
		change(u, y), change(v, x);
		inv[x] = v, inv[y] = u;
	}
	int query(int u)
	{
		if (u <= 1 || u > n)
		{
			fprintf(stderr, "Invalid call of query(%d)!", u);
			exit(0);
		}
		if (++cnt2 > lim2)
		{
			fprintf(stderr, "Too many queries!\n");
			exit(0);
		}
		int res = 0;
		bool flag = true;
		for (; u; u = fa[u])
		{
			if (flag)
				res = max(res, max(perm[u], mx[ch[u][0]]));
			if (is_root[u])
				flag = true;
			else if (ch[fa[u]][0] == u)
				flag = false;
			else
				flag = true;
		}
		return res;
	}
	void answer(vector<int> par, vector<int> val)
	{
		if (par.size() != n - 1 || val.size() != n - 1)
		{
			fprintf(stderr, "Invalid output!\n");
			return;
		}
		for (int i = 2; i <= n; i++)
		{
			if (par[i - 2] != p[i])
			{
				fprintf(stderr, "The answer to p[%d] is wrong! The right answer is %d, but you output %d.\n", i, p[i], par[i - 2]);
				return;
			}
		}
		for (int i = 2; i <= n; i++)
		{
			if (val[i - 2] != v[i])
			{
				fprintf(stderr, "The answer to v[%d] is wrong! The right answer is %d, but you output %d.\n", i, v[i], val[i - 2]);
				return;
			}
		}
		printf("Right output! cnt1 = %d, cnt2 = %d.\n", cnt1, cnt2);
	}
}
void solve(int n, int lim1, int lim2);
void exchange(int x , int y){return grader::exchange(x , y);}
int query(int x){return grader::query(x);}
void answer(vector<int>par, vector<int>val){return grader::answer(par,val);}
int main()
{
	grader::init();
	solve(grader::n, grader::lim1, grader::lim2);
	return 0;
}