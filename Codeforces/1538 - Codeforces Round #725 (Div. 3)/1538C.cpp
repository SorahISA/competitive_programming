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
#define pf pop_front
#define pb pop_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

void solve() {
    int N, L, R; cin >> N >> L >> R;
    
    vector<int> arr(N);
    for (auto &x : arr) cin >> x;
    sort(ALL(arr));
    
    int ans = 0;
    for (auto &x : arr) {
        auto lo = lower_bound(ALL(arr), L - x);
        auto hi = upper_bound(ALL(arr), R - x);
        ans += hi - lo;
        if (L <= 2*x and 2*x <= R) --ans;
    }
    cout << ans / 2 << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}