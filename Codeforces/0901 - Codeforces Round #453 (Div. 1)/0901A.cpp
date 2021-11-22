#pragma GCC optimize("O3", "unroll-loops")

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
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define pb push_back
#define fastIO() ios_base::sync_with_stdio(false), cin.tie(0)

const int mod = 998244353;

int32_t main() {
	fastIO();
	
	int h, n = 0;
	cin >> h;
	
	vector<int> v(h+1);
	for (auto &x : v) cin >> x, n += x;
	
	for (int i = 1; i <= h; ++i) {
		if (v[i] > 1 and v[i-1] > 1) {
			cout << "ambiguous\n";
			break;
		}
		if (i == h) {
			cout << "perfect\n";
			return 0;
		}
	}
	
	cout << 0 << " ";
	for (int i = 1, tok = 1; i <= h; tok += v[i-1], ++i) {
		for (int j = 0; j < v[i]; ++j) {
			cout << tok + (j > 0 and v[i-1] > 1) << " ";
		}
	}
	cout << "\n";
	
	cout << 0 << " ";
	for (int i = 1, tok = 1; i <= h; tok += v[i-1], ++i) {
		for (int j = 0; j < v[i]; ++j) {
			cout << tok << " ";
		}
	}
	cout << "\n";
	
	return 0;
}