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
	
	int n, m, k;
	cin >> n >> m >> k;
	
	int dp[n+1][k+1];
	memset(dp, 0x00, sizeof(dp));
	
	dp[1][0] = m;
	for (int i = 2; i <= n; ++i) {
		for (int j = 0; j <= min(i-1, k); ++j) {
			dp[i][j] = dp[i-1][j] + (j ? dp[i-1][j-1] * (m-1) : 0);
			dp[i][j] %= mod;
		}
	}
	
	cout << dp[n][k] << "\n";
	
	return 0;
}