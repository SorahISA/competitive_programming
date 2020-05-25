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

	int a, b, c, A[5], B[5];
	cin >> a >> b >> c;
	for (int i = 0; i < 5; ++i) cin >> A[i];
	for (int i = 0; i < 5; ++i) cin >> B[i];

	int win = 0, db = 1;
	for (int i = 0; i < 5; ++i) {
		if (a == A[i]) win += B[i];
		if (b == A[i]) win += B[i];
		if (c == A[i]) win -= B[i], db = 0;
	}

	cout << max(0LL, win * (db + 1)) << "\n";

	return 0;
}
