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
const int mxn = 3e4 + 5, mod = 1e9 + 7, MOD = 1e9 + 7, mod2 = 998244353;

int a[mxn], n;
vector<int> tre[mxn * 4];
void merge(int cur, int l, int r) {
	int p1 = 0, p2 = 0, f1 = tre[l].size(), f2 = tre[r].size();
	while (p1 < f1 || p2 < f2) {
		if (p1 == f1)
			tre[cur].push_back(tre[r][p2++]);
		else if (p2 == f2)
			tre[cur].push_back(tre[l][p1++]);
		else {
			if (tre[r][p2] < tre[l][p1]) {
				tre[cur].push_back(tre[r][p2++]);
			} else {
				tre[cur].push_back(tre[l][p1++]);
			}
		}
	}
}
void build(int node, int l, int r) {
	if (l == r) {
		tre[node].push_back(a[l]);
		return;
	}
	int mid = (l + r) / 2;
	build(node * 2, l, mid);
	build(node * 2 + 1, mid + 1, r);
	merge(node, node * 2, node * 2 + 1);
	return;
}
int get(int node, int val) {
	int pl = upper_bound(tre[node].begin(), tre[node].end(), val)
			- tre[node].begin();
	return tre[node].size() - pl;
}
int qry(int node, int l, int r, int ql, int qr, int qval) {
	if (ql > r || qr < l)
		return 0;
	if (ql <= l && qr >= r) {
		return get(node, qval);
	}
	int mid = (l + r) / 2;
	return qry(node * 2, l, mid, ql, qr, qval)
			+ qry(node * 2 + 1, mid + 1, r, ql, qr, qval);
}
void bingo() {
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	build(1, 0, n - 1);
	int q;
	cin >> q;
	while (q--) {
		int i, j, k;
		cin >> i >> j >> k;
		cout << qry(1, 0, n - 1, i - 1, j - 1, k) << '\n';
	}
}

int main() {
	go
#ifdef LOCAL
	freopen("input.in", "rt", stdin);
//	freopen("output.out", "wt", stdout);
#endif
	//freopen("card.in", "rt", stdin);
	int t = 1;
//	cin >> t;
	while (t--) {
		bingo();
	}
	return 0;
}
