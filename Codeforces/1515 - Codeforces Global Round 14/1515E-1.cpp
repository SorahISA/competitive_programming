#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = std::priority_queue<T>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % (uint64_t)(R - L + 1) + L);
}

template<typename T1, typename T2>
ostream& operator << (ostream &os, pair<T1, T2> p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream &os, vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

/*
void test(int n) {
    vector<int> perm(n);
    iota(ALL(perm), 0);
    
    set<vector<int>> valid;
    do {
        vector<int> light(n, 0), valid_perm;
        for (int i = 0; i < n; ++i) {
            if (light[perm[i]] == 1) continue;
            light[perm[i]] = 1, valid_perm.eb(perm[i]);
            for (int j = 1; j < n-1; ++j) {
                if (light[j-1] and light[j+1]) light[j] = 1;
            }
        }
        valid.insert(valid_perm);
    } while (next_permutation(ALL(perm)));
    cout << valid.size() << "\n";
    
    for (auto vec : valid) cout << vec << "\n";
}
*/

/// ans = {1, 2, 6, 20, 78, 344, 1680, 8960, 51768, ...} ///

void solve() {
    int n, mod; cin >> n >> mod;
    
    int pow2[n+1], cnm[n+1][n+1], dp[n+1][n+1];
    memset(cnm, 0x00, sizeof(cnm));
    memset(dp, 0x00, sizeof(dp));
    
    pow2[0] = 1;
    for (int i = 1; i <= n; ++i) pow2[i] = pow2[i-1] * 2 % mod;
    
    for (int i = 0; i <= n; ++i) {
        cnm[i][0] = cnm[i][i] = 1;
        for (int j = 1; j <= i-1; ++j) {
            cnm[i][j] = (cnm[i-1][j-1] + cnm[i-1][j]) % mod;
        }
    }
    
    /// the ways to manually fully light an array of length N is 2^{N-1} ///
    /// pick a k \in [1, N] and light k, k+1, k+2, ..., N and k-1, k-2, ..., 1 in this order ///
    /// (not necessary have to be continuous) ///
    /// (N-1, 0) + (N-1, 1) + (N-1, 2) + ... + (N-1, N-1) = 2^{N-1} ///
    
    /// dp[i][j]: finish with [1, i] (next place to light is i+2) and there are j manuals ///
    /// since you have to light some continuous segments with exactly one gap between ///
    /// dp[i][j] = \sum_{k=1}^{i-2}{dp[k][j-(i-k-1)] * (j, i-k-1)} ///
    /// the answer is \sum{dp[N][*]} ///
    
    for (int i = 1; i <= n; ++i) dp[i][i] = pow2[i-1];
    for (int i = 3; i <= n; ++i) {
        for (int j = i/2+1; j < i; ++j) {
            // cout << pii{i, j} << " from:\n";
            for (int k = 1; k <= i-2; ++k) {
                dp[i][j] += dp[k][j-(i-k-1)] * cnm[j][i-k-1] % mod * pow2[(i-k-1)-1] % mod;
                // cout << pii{k, j-(i-k-1)} << " ";
            }
            // cout << "\n";
            dp[i][j] %= mod;
        }
    }
    
    int ans = 0;
    for (int i = 0; i <= n; ++i) ans += dp[n][i];
    cout << ans % mod << "\n";
    
    // for (int i = 0; i <= n; ++i) {
        // for (int j = 0; j <= n; ++j) cout << dp[i][j] << " \n"[j == n];
    // }
}

int32_t main() {
    fastIO();
    
    // test(4);
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}