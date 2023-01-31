#include "testlib.h"
using std::vector;

constexpr int N = 2054;

int p[N], G[N][N], tag[N];

void work(int testcase) {
	int n = inf.readInt(), m = inf.readInt();

	for (int i = 1; i <= n; ++i) memset(G[i] + 1, -1, n << 2);
	for (int i = 0; i < m; ++i) {
		int k = inf.readInt();
		vector<int> a = inf.readInts(k);
		for (int v = 1; v < k; ++v)
			for (int u = 0; u < v; ++u)
				G[ a[u] ][ a[v] ] = G[ a[v] ][ a[u] ] = i;
	}
	for (int v = 2; v <= n; ++v)
		for (int u = 1; u < v; ++u)
			if (!~G[u][v]) G[u][v] = G[v][u] = m++;

	*p = ouf.readInt(-1, n, "p[1]");
	switch (*p) {
		case -1:
			ouf.ensuref(!~ans.readInt(), "[testcase #%d] You didn't find the solution while jury did.", testcase);
			return;
		case 0:
			ouf.quitf(_pe, "[testcase %d] Unexpected p[1] = 0.", testcase);
	}

	if (~ans.readInt()) ans.readInts(n - 1);

	vector<int> tmp_ = ouf.readInts(n - 1, 1, n, "p", 2);
	memcpy(p + 1, tmp_.data(), (n - 1) << 2);

	memset(tag + 1, -1, n << 2);
	for (int i = 0; i < n; ++i) {
		ouf.ensuref(
			!~tag[p[i]],
			"[testcase %d] p[%d] = p[%d] = %d.",
			testcase, tag[p[i]] + 1, i + 1, p[i]
		);
		tag[p[i]] = i;
	}

	p[n] = *p, p[n + 1] = p[1];
	for (int i = 0; i < n; ++i)
		ouf.ensuref(
			G[ p[i] ][ p[i + 1] ] != G[ p[i] ][ p[i + 2] ],
			"[testcase %d] p[%d] = %d, p[%d] = %d, p[%d] = %d are in the same group #%d.",
			testcase, i + 1, p[i], (i + 1) % n + 1, p[i + 1],
			(i + 2) % n + 1, p[i + 2], G[ p[i] ][ p[i + 1] ] + 1
		);
}

int main(int argc, char *argv[]) {
	registerTestlibCmd(argc, argv);

	int T = inf.readInt();
	for (int t = 0; t < T; work(++t));

	ouf.quits(_ok, vtos(T) + " testcase" + (T == 1 ? "" : "s"));
	return 0;
}
