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

const int mod = 1E9 + 7;
const int maxn = 1000 + 5;
const int dig = 9;

int dp[maxn][1<<dig][dig];

void solve() {
	int P, Q;
	cin >> P >> Q;
	// for (int i = 0; i < dig; ++i) cout << dp[P][(1<<dig)-1][i] << "\n";
	cout << dp[P][(1<<dig)-1][Q-1] << "\n";
}

void init() {
	for (int k = 0; k < dig; ++k) dp[1][1<<k][k] = 1;
	for (int i = 2; i < maxn; ++i) {
		for (int j = 1; j < (1<<dig); ++j) {
			for (int k = 0; k < dig; ++k) dp[i][j][k] = dp[i-1][j][k];
			for (int k = 0; k < dig; ++k) {
				if (j >> k & 1) {
					int _j = j ^ (1 << k);
					for (int l = max(0LL, k-2); l <= min(dig-1, k+2); ++l) {
						if (_j >> l & 1) dp[i][j][k] += dp[i-1][_j][l] + dp[i-1][j][l];
					}
				}
				dp[i][j][k] %= mod;
				// printf("dp[%lld][%lld][%lld] = %lld\n", i, j, k, dp[i][j][k]);
			}
		}
	}
}

int32_t main() {
	// fastIO();
	init();

	int t;
	cin >> t;
	while (t--) solve();

	return 0;
}
