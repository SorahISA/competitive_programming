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

template<class T>
ostream& operator << (ostream& os, vector<T> vec) {
    int sz = vec.size();
    for (int i = 0; i < sz; ++i) {
        os << vec[i];
        if (i != sz-1) os << " ";
    }
    return os;
}

void solve() {
    int n, c; cin >> n >> c;
    if (c < n-1 or c >= n*(n+1)/2) return cout << "IMPOSSIBLE\n", void();
    c -= n-1;
    
    vector<pii> op;
    for (int i = 0; i < n; ++i) op.eb(i, i + min(c, n-i-1)), c -= min(c, n-i-1);
    reverse(ALL(op));
    
    vector<int> ans(n); iota(ALL(ans), 1);
    for (auto [L, R] : op) reverse(begin(ans) + L, begin(ans) + R+1);
    cout << ans << "\n";
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