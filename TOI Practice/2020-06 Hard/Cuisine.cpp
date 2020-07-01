#pragma GCC optimize("Ofast", "unroll-loops")

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = priority_queue<T>;
template<typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define ALL(x) x.begin(), x.end()
#define eb emplace_back
#define pb push_back
#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0)

const int maxn = 1 << 18;

int BIT[maxn];

void Add(int idxL, int idxR, int val) {
	while (idxR) BIT[idxR] += val, idxR -= idxR & -idxR;
	while (idxL) BIT[idxL] -= val, idxL -= idxL & -idxL;
}

int Sum(int idx, int ans = 0) {
	if (idx == 0) return ans;
	while (idx < maxn) ans += BIT[idx], idx += idx & -idx;
	return ans;
}

int32_t main() {
	fastIO();
	
	int n, q, A, tmp;
	cin >> n >> q >> A;
	
	for (int i = 1; i <= n; ++i) cin >> tmp, Add(i-1, n, tmp);
	
	int op, id, w;
	while (q--) {
		cin >> op;
		if (op == 0) {
			int ans = 0, L = 1, R = n;
			while (L <= R) {
				// cout << L << "\n";
				++ans;
				int lo = L, hi = R, mi, val, pre = Sum(L - 1);
				while (lo < hi) {
					// cout << lo << " " << hi << "\n";
					mi = lo + hi + 1 >> 1, val = Sum(mi) - pre;
					if (val > A) hi = mi - 1;
					else     	 lo = mi;
				}
				L = lo + 1;
			}
			cout << ans << "\n";
		}
		else if (op == 1) cin >> id >> w, Add(id-1, n,  w);
		else if (op == 2) cin >> id >> w, Add(id-1, n, -w);
	}
	
	return 0;
}
