#include <bits/stdc++.h>
#include <ext/numeric>

#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/rope>
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
template<class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
typedef tree<int, null_type, less<int>, rb_tree_tag,
		tree_order_statistics_node_update> ordered_set;
using namespace std;
#define go ios::sync_with_stdio(0);cin.tie(nullptr);cout.tie(nullptr);
#define ll long long
typedef vector<vector<int>> vvi;
typedef complex<long double> Point;
const double Pi = acos(-1.0), eps = 1e-8;
#define S second
#define F first
#define X real()
#define Y imag()
#define Angle(v) (atan2((v).Y , (v).X))
#define Length(v) ((long double)hypot((v).Y , (v).X))
#define Lengthsqr(v) (dot((v) , (v)))
const int mxn = 1e4 + 5, mod = 1e9 + 7, MOD = 1e9 + 7, mod2 = 998244353;

int n, d[mxn], st[mxn], et[mxn], timer;
vector<array<int, 2>> vi[mxn];
int pmq[mxn][20], lvl[mxn];
void init() {
	timer = 0;
	for (int i = 1; i <= n; i++) {
		vi[i].clear();
		d[i] = st[i] = et[i] = lvl[i] = 0;
	}
}
void dfs1(int node, int par, int cost, int level = 0) {
	lvl[node] = level;
	pmq[node][0] = par;
	st[node] = ++timer;
	d[node] = cost;
	for (auto it : vi[node]) {
		if (it[0] != par) {
			dfs1(it[0], node, cost + it[1], level + 1);
		}
	}
	et[node] = ++timer;
}
bool is_anc(int anc, int node) {
	return st[anc] <= st[node] && et[anc] >= et[node];
}
int get_lca(int u, int v) {
	int lca = u;
	for (int i = 19; i >= 0; i--) {
		if (pmq[lca][i] <= 0)
			continue;
		if (!is_anc(pmq[lca][i], u) || !is_anc(pmq[lca][i], v))
			lca = pmq[lca][i];
	}
	lca = pmq[lca][0];
	return lca;
}
int dist(int u, int v) {
	if (is_anc(u, v))
		return d[v] - d[u];
	if (is_anc(v, u))
		return d[u] - d[v];
	// we need lca node
	int lca = get_lca(u, v);
	return (d[u] - d[lca]) + (d[v] - d[lca]);
}
int kth(int u, int v, int k) {
	if (is_anc(u, v)) {
		k = (abs(lvl[u] - lvl[v])) - k;
		swap(u, v);
		for (int i = 19; i >= 0; i--) {
			if (k >= (1 << i)) {
				k -= (1 << i);
				u = pmq[u][i];
			}
		}
		return u;
	}
	if (is_anc(v, u)) {
		for (int i = 19; i >= 0; i--) {
			if (k >= (1 << i)) {
				k -= (1 << i);
				u = pmq[u][i];
			}
		}
		return u;
	}
	int lca = get_lca(u, v);
	if (abs(lvl[lca] - lvl[u]) > k) {
		for (int i = 19; i >= 0; i--) {
			if (k >= (1 << i)) {
				k -= (1 << i);
				u = pmq[u][i];
			}
		}
		return u;
	} else if (lvl[lca] - lvl[u] == k) {
		return lca;
	} else {
		k -= abs((lvl[lca] - lvl[u]));
		u = lca;
		k = abs((lvl[u] - lvl[v])) - k;
		swap(u, v);
		for (int i = 19; i >= 0; i--) {
			if (k >= (1 << i)) {
				k -= (1 << i);
				u = pmq[u][i];
			}
		}
		return u;
	}
}
void bingo() {
	cin >> n;
	init();
	for (int i = 0; i < n - 1; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		vi[u].push_back( { v, c });
		vi[v].push_back( { u, c });
	}
	dfs1(1, -1, 0);
	int lg = log2(n);
	++lg;
	for (int i = 1; i <= lg; i++) {
		for (int j = 1; j <= n; j++) {
			pmq[j][i] = pmq[pmq[j][i - 1]][i - 1];
		}
	}
	string s;
	while (cin >> s) {
		if (s == "DONE")
			break;
		if (s == "DIST") {
			int u, v;
			cin >> u >> v;
			cout << dist(u, v) << '\n';
		} else {
			int u, v, k;
			cin >> u >> v >> k;
			cout << kth(u, v, k - 1) << '\n';
		}
	}
	cout << '\n';
}

int main() {
	go
#ifdef LOCAL
	freopen("input.in", "rt", stdin);
//	freopen("output.out", "wt", stdout);
#endif
	//freopen("card.in", "rt", stdin);
	int t = 1;
	cin >> t;
	while (t--) {
		bingo();
	}
	return 0;
}
