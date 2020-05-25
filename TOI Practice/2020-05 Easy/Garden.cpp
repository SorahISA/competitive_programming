#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = priority_queue<T>;

#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define pb push_back

#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

int32_t main() {
	fastIO();

	int n;
	cin >> n;

	vector<int> v(n);
	for (auto &x : v) cin >> x;

	int L = -1, R = -1, cnt = 0;
	for (int i = 0; i < n; ++i) {
		if (v[i] == 1 and L == -1) L = i;
		if (v[i] == 1) R = i;
	}

	for (int i = L; i <= R; ++i) {
		if (!v[i] and v[i-1] != 9 and v[i+1] != 9) ++cnt;
	}

	cout << cnt << "\n";

	return 0;
}
