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

template<typename T>
ostream& operator << (ostream &os, vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

void solve() {
    int n; cin >> n;
    
    vector<int> v(n), ans(3*n);
    for (auto &x : v) cin >> x;
    
    int sum = accumulate(ALL(v), 0) / 3;
    for (int i = 3; i < 3*n; ++i) {
        ans[i] = ans[i-3] + v[(i-1)%n] - v[(i-2)%n];
    }
    
    if (n % 3 == 1) {
        /// ans[0] = x, ans[n] = y+k, ans[2n] = z+l ///
        /// v[1] = x + y + z ///
        int x = (v[1] + ans[n] + ans[2*n]) / 3;
        int y = x - ans[n];
        int z = x - ans[2*n];
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) ans[i] += x;
            if (i % 3 == 1) ans[i] += y;
            if (i % 3 == 2) ans[i] += z;
        }
        ans.resize(n);
    }
    
    if (n % 3 == 2) {
        /// ans[0] = x, ans[n] = z+k, ans[2n] = y+l ///
        /// v[1] = x + y + z ///
        int x = (v[1] + ans[n] + ans[2*n]) / 3;
        int z = x - ans[n];
        int y = x - ans[2*n];
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) ans[i] += x;
            if (i % 3 == 1) ans[i] += y;
            if (i % 3 == 2) ans[i] += z;
        }
        ans.resize(n);
    }
    
    if (n % 3 == 0) {
        /// ans[0] = x, ans[3k] = x-k0 ///
        /// v[1] = x + y + z ///
        vector<int> minVal(3, 0);
        for (int i = 0; i < n; ++i) minVal[i%3] = min(minVal[i%3], ans[i]);
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) ans[i] -= minVal[0];
            if (i % 3 == 1) ans[i] -= minVal[1];
            if (i % 3 == 2) ans[i] += v[1] + minVal[0] + minVal[1];
        }
        ans.resize(n);
    }
    
    cout << ans << "\n";
    // for (int i = 2*n; i < 3*n; ++i) cout << ans[i] << " \n"[i == 3*n-1];
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}