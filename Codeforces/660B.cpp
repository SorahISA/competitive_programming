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
	
	int n, m, tok = 0;
	cin >> n >> m;
	
	int arr[4][n];
	for (int i = 0; i < n; ++i) {
		arr[0][i] = ++tok;
		arr[3][i] = ++tok;
	}
	for (int i = 0; i < n; ++i) {
		arr[1][i] = ++tok;
		arr[2][i] = ++tok;
	}
	
	for (int i = 0; i < n; ++i) {
		if (arr[1][i] <= m) cout << arr[1][i] << " ";
		if (arr[0][i] <= m) cout << arr[0][i] << " ";
		if (arr[2][i] <= m) cout << arr[2][i] << " ";
		if (arr[3][i] <= m) cout << arr[3][i] << " ";
	}
	cout << "\n";
	
	return 0;
}