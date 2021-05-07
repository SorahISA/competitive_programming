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

const int maxl = 35; /// 32*33/2 = 528 > 500

void solve() {
    int R, B; cin >> R >> B;
    
    int dp[maxl][R+1][B+1];
    memset(dp, 0x00, sizeof(dp));
    /// dp[i][j][k]: maximum pairs constructed in the i-th layer (where all pairs are (i, *)), ///
    ///     and there are j Rs left and k Bs left ///
    
    for (int i = 0; i < maxl; ++i) {
        /// every R-cost is i in this layer ///
        for (int j = 0; j <= R; ++j) {
            for (int k = 0; k <= B; ++k) {
                for (int l = 0; l < maxl; ++l) {
                    /// pick from (i, 0) to (i, l) ///
                    int useR = i*(l+1), useB = l*(l+1)/2;
                    if (j < useR or k < useB) break;
                    dp[i][j][k] = max(dp[i][j][k], (i ? dp[i-1][j-useR][k-useB] : (int)0) + (l + 1));
                }
            }
        }
    }
    
    int ans = 0;
    for (int i = 0; i < maxl; ++i) {
        for (int j = 0; j <= R; ++j) {
            for (int k = 0; k <= B; ++k) {
                // printf("dp[%I64d][%I64d][%I64d]: %I64d\n", i, j, k, dp[i][j][k]);
                ans = max(ans, dp[i][j][k]);
            }
        }
    }
    cout << ans-1 << "\n"; /// minus (0, 0)
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}