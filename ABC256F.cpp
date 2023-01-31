#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
using std::cin;
#else
std::ifstream cin("ABC256F.in");
#endif
using std::cout;

const int mod = 998244353, inv = mod / 2 + 1;

class BIT
{
private:
	int n, *t;
	int lowbit(int);

public:
	BIT(int);
	void modify(int, int);
	int query(int);
};

BIT::BIT(int _n) : n(_n), t(new int[_n + 1]()) {}

int BIT::lowbit(int x) { return x & -x; }

void BIT::modify(int x, int v)
{
	for (int i = x; i <= n; i += lowbit(i))
		t[i] = (t[i] + v) % mod;
}

int BIT::query(int x)
{
	int ret = 0;
	for (int i = x; i > 0; i -= lowbit(i))
		ret = (ret + t[i]) % mod;
	return ret;
}

int main()
{
	int n, q;
	cin >> n >> q;
	int *a = new int[n + 1];
	BIT sum(n), mul(n), pw(n);
	for (int i = 1; i <= n; ++i)
	{
		cin >> a[i];
		a[i] %= mod;
		sum.modify(i, a[i]);
		mul.modify(i, 1ll * i * a[i] % mod);
		pw.modify(i, 1ll * i * i % mod * a[i] % mod);
	}
	for (int i = 0; i < q; ++i)
	{
		int op;
		cin >> op;
		switch (op)
		{
		case 1:
		{
			int x, v;
			cin >> x >> v;
			v %= mod;
			sum.modify(x, (v - a[x]) % mod);
			mul.modify(x, 1ll * x * ((v - a[x]) % mod) % mod);
			pw.modify(x, 1ll * x * x % mod * ((v - a[x]) % mod) % mod);
			a[x] = v;
			break;
		}
		case 2:
		{
			int x;
			cin >> x;
			cout << (1ll * inv * ((pw.query(x) - 1ll * (x * 2ll % mod + 3) % mod * mul.query(x) % mod) % mod + 1ll * (((1ll * x * x % mod + x * 3ll % mod) % mod + 2) % mod) * sum.query(x) % mod) % mod + mod) % mod << '\n';
			break;
		}
		}
	}
	return 0;
}