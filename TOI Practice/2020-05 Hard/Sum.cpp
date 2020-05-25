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

const int mod = 1E9 + 9;

int A, B;

int calc(int x) {
	/// a b 0 | xi-1 ///
	/// 1 0 0 | xi-2 ///
	/// a b 1 | Si-1 ///

	int base[3][3] = {
		{A, B, 0},
		{1, 0, 0},
		{A, B, 1},
	};

	int ans[3][3] = {
		{1, 0, 0},
		{0, 1, 0},
		{0, 0, 1},
	};

	int tmp[3][3];

	x -= 2;
	while (x) {
		if (x & 1) {
			/// ans = ans * base ///

			for (int i = 0; i < 3; ++i) {
				for (int j = 0; j < 3; ++j) tmp[i][j] = 0;
			}

			for (int i = 0; i < 3; ++i) {
				for (int j = 0; j < 3; ++j) {
					for (int k = 0; k < 3; ++k) {
						tmp[i][k] += ans[i][j] * base[j][k];
					}
				}
			}

			for (int i = 0; i < 3; ++i) {
				for (int j = 0; j < 3; ++j) ans[i][j] = tmp[i][j] % mod;
			}
		}

		/// base = base * base ///
		
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) tmp[i][j] = 0;
		}

		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				for (int k = 0; k < 3; ++k) {
					tmp[i][k] += base[i][j] * base[j][k];
				}
			}
		}

		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) base[i][j] = tmp[i][j] % mod;
		}

		/// x >>= 1 ///

		x >>= 1;
	}

#ifdef local
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) cout << ans[i][j] << " \n"[j == 2];
	}
#endif
	
	return (ans[2][0] + ans[2][1] + 2*ans[2][2]) % mod;
}

int32_t main() {
	fastIO();

	int lb, ub;
	cin >> A >> B >> lb >> ub;

	cout << (calc(ub) - calc(lb-1) + mod) % mod << "\n";

	return 0;
}
